// =====================================================================
//  camera_setup.h  -  OV2640 / OV5640 init with runtime auto-detection
// =====================================================================
#pragma once
#include <esp_camera.h>

namespace cam {

// Initializes the DVP camera. The SCCB control bus shares the I2C pins
// (IO1/IO2) with the touch + PMU, so call Wire.begin() BEFORE this.
// Returns true on success. Auto-detects OV2640 vs OV5640 and applies a
// suitable framesize from config.h.
bool begin();

// Human readable sensor name ("OV2640", "OV5640", "?").
const char *sensorName();

// Current capture dimensions (after init).
uint16_t width();
uint16_t height();

}  // namespace cam
