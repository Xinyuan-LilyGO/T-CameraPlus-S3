// =====================================================================
//  sd_storage.cpp  -  see sd_storage.h
// =====================================================================
#include "sd_storage.h"
#include "spi_bus.h"
#include "board_pins.h"
#include "config.h"
#include <Arduino.h>
#include <SD.h>
#include <Preferences.h>

namespace storage {

static bool s_mounted = false;
static Preferences s_prefs;

bool begin() {
    // 20 MHz is a safe shared-bus speed; raise cautiously if your card allows.
    if (!SD.begin(PIN_SD_CS, spibus::spi(), 40000000)) {
        log_e("SD mount failed");
        s_mounted = false;
        return false;
    }
    uint8_t type = SD.cardType();
    if (type == CARD_NONE) { log_e("no SD card"); s_mounted = false; return false; }

    if (!SD.exists(REC_DIR))   SD.mkdir(REC_DIR);
    if (!SD.exists(PHOTO_DIR)) SD.mkdir(PHOTO_DIR);

    s_prefs.begin("dashcam", false);
    s_mounted = true;
    log_i("SD ok: %llu MB total, %lu MB free",
          SD.totalBytes() / (1024ULL * 1024ULL), (unsigned long)freeMB());
    return true;
}

bool     mounted()    { return s_mounted; }
uint64_t totalBytes() { return s_mounted ? SD.totalBytes() : 0; }
uint64_t freeBytes()  { return s_mounted ? (SD.totalBytes() - SD.usedBytes()) : 0; }
uint32_t freeMB()     { return (uint32_t)(freeBytes() / (1024ULL * 1024ULL)); }

static uint32_t nextCounter() {
    uint32_t n = s_prefs.getUInt("clipno", 0) + 1;
    s_prefs.putUInt("clipno", n);
    return n;
}

void nextClipPath(char *out, size_t outLen) {
    snprintf(out, outLen, "%s/%s%06lu%s",
             REC_DIR, REC_FILE_PREFIX, (unsigned long)nextCounter(), REC_FILE_EXT);
}

void nextPhotoPath(char *out, size_t outLen) {
    uint32_t n = s_prefs.getUInt("photono", 0) + 1;
    s_prefs.putUInt("photono", n);
    snprintf(out, outLen, "%s/%s%06lu.jpg", PHOTO_DIR, PHOTO_FILE_PREFIX, (unsigned long)n);
}

// Parse the numeric suffix out of "CLIP_000123.avi" -> 123, or -1 if no match.
static long clipIndex(const char *name) {
    size_t pfx = strlen(REC_FILE_PREFIX);
    if (strncmp(name, REC_FILE_PREFIX, pfx) != 0) return -1;
    const char *p = name + pfx;
    long v = 0; bool any = false;
    while (*p >= '0' && *p <= '9') { v = v * 10 + (*p - '0'); p++; any = true; }
    if (!any) return -1;
    return v;
}

static bool deleteOldestClip() {
    File dir = SD.open(REC_DIR);
    if (!dir) return false;

    char oldest[96] = {0};
    long oldestIdx = -1;
    for (File f = dir.openNextFile(); f; f = dir.openNextFile()) {
        if (!f.isDirectory()) {
            const char *full = f.name();                 // may be full path
            const char *base = strrchr(full, '/');
            base = base ? base + 1 : full;
            long idx = clipIndex(base);
            if (idx >= 0 && (oldestIdx < 0 || idx < oldestIdx)) {
                oldestIdx = idx;
                snprintf(oldest, sizeof(oldest), "%s/%s", REC_DIR, base);
            }
        }
        f.close();
    }
    dir.close();

    if (oldestIdx < 0) return false;                     // nothing to delete
    bool ok = SD.remove(oldest);
    log_w("loop-delete %s -> %s", oldest, ok ? "ok" : "FAILED");
    return ok;
}

bool ensureFreeSpace(uint32_t minFreeMB) {
    if (!s_mounted) return false;
    int guard = 0;
    while (freeMB() < minFreeMB) {
        if (!deleteOldestClip()) return false;           // can't free more
        if (++guard > 10000) return false;               // safety
    }
    return true;
}

}  // namespace storage
