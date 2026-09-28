// =====================================================================
//  recorder.cpp  -  see recorder.h
// =====================================================================
#include "recorder.h"
#include "avi_writer.h"
#include "camera_setup.h"
#include "audio_mic.h"
#include "sd_storage.h"
#include "spi_bus.h"
#include "config.h"
#include <Arduino.h>
#include <esp_camera.h>
#include <SD.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace recorder {

// ---- SD-backed AVI sink ---------------------------------------------
struct FileSink : public AviSink {
    File f;
    size_t   write(const void *d, size_t n) override { return f.write((const uint8_t *)d, n); }
    bool     seek(uint32_t p) override               { return f.seek(p); }
    uint32_t pos() override                          { return f.position(); }
    void     flush() override                        { f.flush(); }
};

// ---- state ----------------------------------------------------------
static AviWriter  s_avi;
static FileSink   s_sink;
static uint8_t   *s_index = nullptr;          // AVI idx1 scratch (PSRAM)
static uint8_t   *s_audioTmp = nullptr;       // PCM drain buffer
static const size_t AUDIO_TMP = 8192;
static uint8_t   *s_writeBuf = nullptr;       // PSRAM copy of JPEG for early fb_return
static const size_t WRITE_CAP = 200 * 1024;  // 200 KB: fits HD quality-14 frames

static volatile bool s_recording = false;
static volatile bool s_snapReq   = false;
static uint32_t s_segStartMs = 0;
static uint32_t s_segFrames  = 0;
static float    s_fps        = 0.0f;
static uint32_t s_cachedFreeMB = 0;
static char     s_err[48]    = {0};
static uint16_t s_w = 800, s_h = 600;

// ---- preview hand-off (recorder -> UI) ------------------------------
static const size_t PREVIEW_CAP = 220 * 1024;
static uint8_t      *s_preview = nullptr;
static size_t        s_previewLen = 0;
static volatile bool s_previewReady = false;
static SemaphoreHandle_t s_pvMux = nullptr;
static uint32_t      s_pvCounter = 0;

// ---------------------------------------------------------------------
bool begin() {
    s_w = cam::width()  ? cam::width()  : 800;
    s_h = cam::height() ? cam::height() : 600;

    s_index    = (uint8_t *)ps_malloc((size_t)AVI_MAX_INDEX_ENTRIES * 16);
    s_audioTmp = (uint8_t *)malloc(AUDIO_TMP);
    s_preview  = (uint8_t *)ps_malloc(PREVIEW_CAP);
    s_writeBuf = (uint8_t *)ps_malloc(WRITE_CAP);
    s_pvMux    = xSemaphoreCreateMutex();

    if (!s_index || !s_audioTmp || !s_preview || !s_writeBuf || !s_pvMux) {
        snprintf(s_err, sizeof(s_err), "buffer alloc failed");
        log_e("%s", s_err);
        return false;
    }
    s_cachedFreeMB = 0;
    return true;
}

static bool openSegment() {
    // make room first (loop recording)
    storage::ensureFreeSpace(REC_MIN_FREE_MB);

    char path[80];
    storage::nextClipPath(path, sizeof(path));
    s_sink.f = SD.open(path, FILE_WRITE);
    if (!s_sink.f) {
        snprintf(s_err, sizeof(s_err), "open %s failed", path);
        log_e("%s", s_err);
        return false;
    }

    bool ok = s_avi.begin(&s_sink, s_w, s_h,
                          AUDIO_ENABLE ? true : false,
                          audio::sampleRate(), audio::channels(), audio::bits(),
                          s_index, (size_t)AVI_MAX_INDEX_ENTRIES * 16);
    if (!ok) {
        snprintf(s_err, sizeof(s_err), "avi begin failed");
        s_sink.f.close();
        return false;
    }
    if (AUDIO_ENABLE) audio::flush();          // start the clip with fresh audio
    s_segStartMs = millis();
    s_segFrames  = 0;
    s_cachedFreeMB = storage::freeMB();
    log_i("recording -> %s", path);
    return true;
}

static void closeSegment() {
    if (!s_sink.f) return;
    float fps = s_fps > 1.0f ? s_fps : 15.0f;
    s_avi.end(fps);
    s_sink.f.close();
    s_cachedFreeMB = storage::freeMB();
}

void start() {
    if (s_recording) return;
    spibus::Guard g;
    if (openSegment()) s_recording = true;
}

void stop() {
    if (!s_recording) return;
    s_recording = false;
    spibus::Guard g;
    closeSegment();
}

void toggle() { s_recording ? stop() : start(); }
bool isRecording() { return s_recording; }
void requestSnapshot() { s_snapReq = true; }

static void rotateSegment() {
    spibus::Guard g;
    closeSegment();
    if (!openSegment()) s_recording = false;   // give up gracefully on error
}

static void writePhoto(camera_fb_t *fb) {
    char path[80];
    storage::nextPhotoPath(path, sizeof(path));
    spibus::Guard g;
    File pf = SD.open(path, FILE_WRITE);
    if (pf) { pf.write(fb->buf, fb->len); pf.close(); log_i("photo -> %s", path); }
    else    { log_e("photo open failed"); }
}

static void copyPreview(camera_fb_t *fb) {
    if (fb->len > PREVIEW_CAP) return;
    if (xSemaphoreTake(s_pvMux, 0) != pdTRUE) return;   // skip if UI is copying
    memcpy(s_preview, fb->buf, fb->len);
    s_previewLen   = fb->len;
    s_previewReady = true;
    xSemaphoreGive(s_pvMux);
}

void captureLoopOnce() {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) { vTaskDelay(1); return; }

    if (s_snapReq) { s_snapReq = false; writePhoto(fb); }

    if (PREVIEW_ENABLE && (++s_pvCounter % PREVIEW_EVERY_N_FRAMES) == 0)
        copyPreview(fb);

    if (s_recording) {
        // Copy JPEG into PSRAM write buffer, then release the camera frame buffer
        // immediately so the camera can start capturing the next frame while we
        // write the current one to SD. This makes capture and SD write parallel.
        const uint8_t *src = fb->buf;
        size_t         srcLen = fb->len;
        if (s_writeBuf && srcLen <= WRITE_CAP) {
            memcpy(s_writeBuf, fb->buf, srcLen);
            esp_camera_fb_return(fb);
            fb = nullptr;
            src = s_writeBuf;
        }

        // Read audio now (camera is already capturing the next frame in parallel).
        size_t audioLen = 0;
        if (AUDIO_ENABLE) audioLen = audio::read(s_audioTmp, AUDIO_TMP);

        spibus::lock();
        bool ok = s_avi.addVideoFrame(src, srcLen);
        if (ok && audioLen) s_avi.addAudioChunk(s_audioTmp, audioLen);
        spibus::unlock();

        s_segFrames++;
        uint32_t dt = millis() - s_segStartMs;
        if (dt > 500) s_fps = (float)s_segFrames * 1000.0f / (float)dt;

        bool timeUp = dt >= (uint32_t)REC_SEGMENT_SECONDS * 1000UL;
        if (!ok || timeUp || s_avi.indexFull()) rotateSegment();
    }

    if (fb) esp_camera_fb_return(fb);
}

bool getPreview(uint8_t *dst, size_t cap, size_t *outLen) {
    if (!s_previewReady) return false;
    if (xSemaphoreTake(s_pvMux, 0) != pdTRUE) return false;
    bool ok = false;
    if (s_previewReady && s_previewLen <= cap) {
        memcpy(dst, s_preview, s_previewLen);
        *outLen = s_previewLen;
        s_previewReady = false;
        ok = true;
    }
    xSemaphoreGive(s_pvMux);
    return ok;
}

uint32_t elapsedSec() {
    if (!s_recording) return 0;
    return (millis() - s_segStartMs) / 1000;
}
float       fps()          { return s_fps; }
uint32_t    cachedFreeMB() { return s_cachedFreeMB; }
const char *lastError()    { return s_err; }

}  // namespace recorder
