// =====================================================================
//  display_ui.h  -  ST7789 240x240 live preview + status overlay
//
//  The LCD shares its SPI bus with the SD card, so every draw call locks
//  spibus internally. Only call these from the UI task.
// =====================================================================
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace display {

struct Overlay {
    bool     recording;
    uint32_t elapsedSec;
    uint32_t freeMB;
    int      battPct;       // -1 = unknown
    bool     charging;
    float    fps;
};

bool begin();
void backlight(bool on);

// Decode a JPEG frame and blit it (centered, scaled) then draw the overlay.
void renderFrame(const uint8_t *jpg, size_t len, const Overlay &ov);

// Full-screen text helpers.
void splash(const char *l1, const char *l2);
void message(const char *msg);

}  // namespace display
