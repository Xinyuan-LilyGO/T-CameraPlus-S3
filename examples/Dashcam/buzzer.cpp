// =====================================================================
//  buzzer.cpp  -  short beep feedback via MAX98357A (I2S_NUM_1)
// =====================================================================
#include "buzzer.h"
#include "board_pins.h"
#include <Arduino.h>
#include <driver/i2s.h>
#include <string.h>

namespace buzzer {

static const i2s_port_t PORT = I2S_NUM_1;
static const uint32_t   RATE = 16000;   // Hz

bool begin() {
    pinMode(PIN_MIC_AMP_EN, OUTPUT);
    digitalWrite(PIN_MIC_AMP_EN, LOW);  // enable MAX98357A (shared with mic enable)

    i2s_config_t cfg       = {};
    cfg.mode               = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    cfg.sample_rate        = RATE;
    cfg.bits_per_sample    = I2S_BITS_PER_SAMPLE_16BIT;
    cfg.channel_format     = I2S_CHANNEL_FMT_RIGHT_LEFT;
    cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    cfg.intr_alloc_flags   = ESP_INTR_FLAG_LEVEL1;
    cfg.dma_buf_count      = 4;
    cfg.dma_buf_len        = 128;
    cfg.use_apll           = false;
    cfg.tx_desc_auto_clear = true;

    if (i2s_driver_install(PORT, &cfg, 0, nullptr) != ESP_OK) {
        log_e("buzzer: i2s_driver_install failed");
        return false;
    }

    i2s_pin_config_t pins  = {};
    pins.bck_io_num        = PIN_AMP_BCLK;
    pins.ws_io_num         = PIN_AMP_LRCLK;
    pins.data_out_num      = PIN_AMP_DATA;
    pins.data_in_num       = I2S_PIN_NO_CHANGE;

    if (i2s_set_pin(PORT, &pins) != ESP_OK) {
        log_e("buzzer: i2s_set_pin failed");
        return false;
    }
    return true;
}

void beep(uint32_t freqHz, uint32_t durationMs) {
    const int16_t  AMP         = 8000;
    const uint32_t totalFrames = RATE * durationMs / 1000;
    const uint32_t halfPeriod  = RATE / (freqHz * 2);   // frames per half-cycle

    int16_t buf[128 * 2];   // 128 stereo frames on the stack (~512 bytes)
    uint32_t pos = 0;
    while (pos < totalFrames) {
        uint32_t n = (totalFrames - pos < 128) ? (totalFrames - pos) : 128;
        for (uint32_t i = 0; i < n; ++i, ++pos) {
            int16_t s = ((pos / halfPeriod) & 1) ? AMP : -AMP;
            buf[i * 2]     = s;   // left channel
            buf[i * 2 + 1] = s;   // right channel
        }
        size_t written;
        i2s_write(PORT, buf, n * 4, &written, pdMS_TO_TICKS(50));
    }
    i2s_zero_dma_buffer(PORT);
}

// ---------------------------------------------------------------------------
// WAV playback
// ---------------------------------------------------------------------------

struct WavInfo {
    uint16_t       channels;
    uint32_t       sampleRate;
    uint16_t       bitsPerSample;
    const uint8_t* pcmData;
    size_t         pcmBytes;
};

static bool parseWav(const uint8_t* data, size_t len, WavInfo& out) {
    if (len < 44) return false;
    if (memcmp(data,     "RIFF", 4) != 0) return false;
    if (memcmp(data + 8, "WAVE", 4) != 0) return false;

    bool hasFmt = false, hasData = false;
    size_t pos = 12;
    while (pos + 8 <= len) {
        uint32_t chunkSize;
        memcpy(&chunkSize, data + pos + 4, 4);

        if (memcmp(data + pos, "fmt ", 4) == 0 && chunkSize >= 16) {
            uint16_t fmt;
            memcpy(&fmt,              data + pos + 8,  2);
            memcpy(&out.channels,     data + pos + 10, 2);
            memcpy(&out.sampleRate,   data + pos + 12, 4);
            memcpy(&out.bitsPerSample,data + pos + 22, 2);
            if (fmt != 1) return false;  // PCM only
            hasFmt = true;
        } else if (memcmp(data + pos, "data", 4) == 0) {
            out.pcmData  = data + pos + 8;
            out.pcmBytes = chunkSize;
            // clamp to actual buffer
            size_t avail = (out.pcmData < data + len) ? (data + len - out.pcmData) : 0;
            if (out.pcmBytes > avail) out.pcmBytes = avail;
            hasData = true;
        }

        pos += 8 + ((chunkSize + 1) & ~1u);  // RIFF chunks are word-aligned
        if (hasFmt && hasData) break;
    }
    return hasFmt && hasData;
}

void playWav(const uint8_t* data, size_t len) {
    WavInfo w;
    if (!parseWav(data, len, w)) {
        log_e("buzzer: invalid WAV data");
        return;
    }
    if (w.bitsPerSample != 8 && w.bitsPerSample != 16) {
        log_e("buzzer: unsupported bits per sample %u", w.bitsPerSample);
        return;
    }
    if (w.channels == 0) return;

    if (w.sampleRate != RATE) {
        i2s_set_sample_rates(PORT, w.sampleRate);
    }

    const size_t  CHUNK_FRAMES   = 128;
    const size_t  bytesPerSample = w.bitsPerSample / 8;
    const size_t  bytesPerFrame  = w.channels * bytesPerSample;
    int16_t       outBuf[CHUNK_FRAMES * 2];  // always 16-bit stereo output

    const uint8_t* src    = w.pcmData;
    const uint8_t* srcEnd = w.pcmData + w.pcmBytes;

    while (src < srcEnd) {
        size_t framesLeft = (srcEnd - src) / bytesPerFrame;
        if (framesLeft == 0) break;
        size_t n = (framesLeft < CHUNK_FRAMES) ? framesLeft : CHUNK_FRAMES;

        for (size_t i = 0; i < n; ++i) {
            int16_t left, right;
            if (w.bitsPerSample == 16) {
                int16_t s; memcpy(&s, src, 2); src += 2;
                left = s;
                if (w.channels >= 2) { memcpy(&s, src, 2); src += 2; right = s; }
                else                 { right = left; }
            } else {  // 8-bit unsigned PCM
                left = (int16_t)(*src++ - 128) << 8;
                if (w.channels >= 2) { right = (int16_t)(*src++ - 128) << 8; }
                else                 { right = left; }
            }
            outBuf[i * 2]     = left;
            outBuf[i * 2 + 1] = right;
        }

        size_t written;
        i2s_write(PORT, outBuf, n * 4, &written, pdMS_TO_TICKS(200));
    }

    i2s_zero_dma_buffer(PORT);

    if (w.sampleRate != RATE) {
        i2s_set_sample_rates(PORT, RATE);
    }
}

}  // namespace buzzer
