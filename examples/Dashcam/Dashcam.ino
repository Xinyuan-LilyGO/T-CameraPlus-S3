// =====================================================================
//  main.cpp  -  T-CameraPlus-S3 Dashcam (行车记录器)
//
//  Features:
//    * loop recording to microSD as AVI (Motion-JPEG video + PCM audio)
//    * live preview on the 240x240 ST7789 LCD with status overlay
//    * audio from the I2S digital mic, muxed into each clip
//    * KEY1 (GPIO17) = snapshot saved to /photos
//    * KEY2 (GPIO0)  = toggle recording start / stop
//    * touch tap = snapshot
//
//  Task layout:
//    core 1 : recorder task  (camera capture + SD writes)
//    core 0 : ui task        (LCD preview, touch, buttons, PMU)
//    core 0 : mic task       (I2S capture -> stream buffer)  [audio_mic.cpp]
// =====================================================================
#include <Arduino.h>
#include <Wire.h>
#include <OneButton.h>

#include "board_pins.h"
#include "buzzer.h"
#include "config.h"
#include "spi_bus.h"
#include "display_ui.h"
#include "camera_setup.h"
#include "audio_mic.h"
#include "sd_storage.h"
#include "touch_cst816.h"
#include "power_sy6970.h"
#include "recorder.h"
#include "pizza_wav.h"

static uint8_t *s_uiPreview = nullptr;
static const size_t UI_PREVIEW_CAP = 220 * 1024;

static OneButton s_key1;
static OneButton s_key2;

// ---------------------------------------------------------------------
static void recordTask(void *) {
    for (;;) {
        recorder::captureLoopOnce();
        vTaskDelay(1);                      // feed the idle watchdog
    }
}

// ---------------------------------------------------------------------
static void uiTask(void *) {
    s_uiPreview = (uint8_t *)ps_malloc(UI_PREVIEW_CAP);

    bool     touchPrev = false;
    uint32_t lastPmu   = 0;

    for (;;) {
        // ---- buttons ----
        s_key1.tick();
        s_key2.tick();

        // ---- touch tap = snapshot ----
        uint16_t tx, ty;
        bool t = touch::read(&tx, &ty);
        if (t && !touchPrev) recorder::requestSnapshot();
        touchPrev = t;

        // ---- PMU refresh ~1 Hz ----
        if (millis() - lastPmu > 1000) { power::update(); lastPmu = millis(); }

        // ---- preview + overlay ----
        size_t len = 0;
        if (s_uiPreview && recorder::getPreview(s_uiPreview, UI_PREVIEW_CAP, &len)) {
            display::Overlay ov;
            ov.recording = recorder::isRecording();
            ov.elapsedSec = recorder::elapsedSec();
            ov.freeMB    = recorder::cachedFreeMB();
            ov.battPct   = power::batteryPercent();
            ov.charging  = power::charging();
            ov.fps       = recorder::fps();
            display::renderFrame(s_uiPreview, len, ov);
        } else {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}

// ---------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    delay(300);
    Serial.println("\n=== T-CameraPlus-S3 Dashcam ===");

    // Shared I2C (camera SCCB + touch + PMU) and shared SPI (LCD + SD).
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 400000);
    spibus::begin();

    display::begin();
    display::splash("DASHCAM", "initializing...");

    if (!cam::begin()) { display::message("CAM ERROR"); }

    if (AUDIO_ENABLE) audio::begin();

    bool sd = storage::begin();
    if (!sd) display::message("NO SD CARD");

    touch::begin();
    power::begin();

    if (!recorder::begin()) display::message("MEM ERROR");

    buzzer::begin();

    // Buttons are initialized last: esp_camera_init() resets the GPIO Matrix and
    // may leave GPIO0 (a strapping pin) in a floating state.  Calling setup() here
    // ensures INPUT_PULLUP is the final pad configuration before the tasks start.
    s_key1.setup(PIN_KEY1, true, true);
    s_key1.attachClick([]() { buzzer::playWav(pizza_wav, sizeof(pizza_wav)); recorder::requestSnapshot(); });
    s_key2.setup(PIN_KEY2, true, true);
    s_key2.attachClick([]() { buzzer::beep(880, 50); recorder::toggle(); });

    // Launch tasks.
    xTaskCreatePinnedToCore(recordTask, "rec", 8192, nullptr, 5, nullptr, 1);
    xTaskCreatePinnedToCore(uiTask,     "ui",  8192, nullptr, 3, nullptr, 0);

    if (AUTO_START_RECORDING && sd) recorder::start();

    Serial.printf("sensor=%s  %ux%u  SD=%s\n",
                  cam::sensorName(), cam::width(), cam::height(),
                  sd ? "ok" : "none");
}

void loop() {
    // Everything runs in the tasks above.
    vTaskDelay(pdMS_TO_TICKS(1000));
}
