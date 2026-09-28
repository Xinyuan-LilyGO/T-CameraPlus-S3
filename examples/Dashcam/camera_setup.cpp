// =====================================================================
//  camera_setup.cpp  -  see camera_setup.h
// =====================================================================
#include "camera_setup.h"
#include "board_pins.h"
#include "config.h"
#include <Arduino.h>

namespace cam {

static const char *s_name = "?";
static uint16_t s_w = 0, s_h = 0;

struct FsInfo { framesize_t fs; uint16_t w; uint16_t h; const char *name; };
static const FsInfo k_fsTable[] = {
    { FRAMESIZE_96X96,   96,   96, "96x96"       },
    { FRAMESIZE_QQVGA,  160,  120, "QQVGA"       },
    { FRAMESIZE_QCIF,   176,  144, "QCIF"        },
    { FRAMESIZE_HQVGA,  240,  176, "HQVGA"       },
    { FRAMESIZE_240X240,240,  240, "240x240"     },
    { FRAMESIZE_QVGA,   320,  240, "QVGA"        },
    { FRAMESIZE_CIF,    400,  296, "CIF"         },
    { FRAMESIZE_HVGA,   480,  320, "HVGA"        },
    { FRAMESIZE_VGA,    640,  480, "VGA"         },
    { FRAMESIZE_SVGA,   800,  600, "SVGA"        },
    { FRAMESIZE_XGA,   1024,  768, "XGA"         },
    { FRAMESIZE_HD,    1280,  720, "HD"          },
    { FRAMESIZE_SXGA,  1280, 1024, "SXGA"        },
    { FRAMESIZE_UXGA,  1600, 1200, "UXGA"        },
    { FRAMESIZE_FHD,   1920, 1080, "FHD"         },
    { FRAMESIZE_P_HD,   720, 1280, "P_HD"        },
    { FRAMESIZE_P_3MP,  864, 1536, "P_3MP"       },
    { FRAMESIZE_QXGA,  2048, 1536, "QXGA"        },
    { FRAMESIZE_QHD,   2560, 1440, "QHD"         },
    { FRAMESIZE_WQXGA, 2560, 1600, "WQXGA"       },
    { FRAMESIZE_P_FHD, 1080, 1920, "P_FHD"       },
    { FRAMESIZE_QSXGA, 2560, 1920, "QSXGA"       },
};

static void framesizeToWH(framesize_t fs, uint16_t &w, uint16_t &h) {
    for (const auto &e : k_fsTable) {
        if (e.fs == fs) { w = e.w; h = e.h; return; }
    }
    w = 800; h = 600;
}

static void printSensorCaps(sensor_t *s) {
    log_i("=== Sensor Capabilities ===");
    log_i("Sensor: %s  PID: 0x%04X", s_name, s->id.PID);

    framesize_t maxFs = FRAMESIZE_INVALID;
    const char *fmts = "";
    if (s->id.PID == OV2640_PID) {
        maxFs = FRAMESIZE_UXGA;
        fmts  = "JPEG, YUV422, RGB565, GRAYSCALE";
    } else if (s->id.PID == OV5640_PID) {
        maxFs = FRAMESIZE_QSXGA;
        fmts  = "JPEG, YUV422, RGB565, GRAYSCALE, RGB888";
    } else {
        log_i("  (unknown sensor — skipping cap list)");
        log_i("===========================");
        return;
    }

    log_i("Supported frame sizes:");
    for (const auto &e : k_fsTable) {
        if (e.fs <= maxFs)
            log_i("  [%2d] %-8s  %4ux%-4u", (int)e.fs, e.name, e.w, e.h);
    }
    log_i("Supported pixel formats: %s", fmts);
    log_i("===========================");
}

bool begin() {
    // IR-cut filter control (color mode). Drive a defined level.
    pinMode(PIN_IRCUT_FBC, OUTPUT);
    digitalWrite(PIN_IRCUT_FBC, HIGH);

    camera_config_t cfg = {};
    cfg.pin_pwdn     = CAM_PIN_PWDN;
    cfg.pin_reset    = CAM_PIN_RESET;
    cfg.pin_xclk     = CAM_PIN_XCLK;
    cfg.pin_sccb_sda = CAM_PIN_SIOD;
    cfg.pin_sccb_scl = CAM_PIN_SIOC;
    cfg.pin_d7 = CAM_PIN_D7;  cfg.pin_d6 = CAM_PIN_D6;
    cfg.pin_d5 = CAM_PIN_D5;  cfg.pin_d4 = CAM_PIN_D4;
    cfg.pin_d3 = CAM_PIN_D3;  cfg.pin_d2 = CAM_PIN_D2;
    cfg.pin_d1 = CAM_PIN_D1;  cfg.pin_d0 = CAM_PIN_D0;
    cfg.pin_vsync = CAM_PIN_VSYNC;
    cfg.pin_href  = CAM_PIN_HREF;
    cfg.pin_pclk  = CAM_PIN_PCLK;

    cfg.xclk_freq_hz = CAM_XCLK_HZ;
    cfg.ledc_timer   = LEDC_TIMER_0;
    cfg.ledc_channel = LEDC_CHANNEL_0;

    cfg.pixel_format = PIXFORMAT_JPEG;
    cfg.frame_size   = FRAMESIZE_SVGA;       // start safe, refined after detect
    cfg.jpeg_quality = CAM_JPEG_QUALITY;
    cfg.fb_count     = CAM_FB_COUNT;
    cfg.fb_location  = CAMERA_FB_IN_PSRAM;
    cfg.grab_mode    = CAMERA_GRAB_LATEST;

    // The SCCB bus is the shared I2C bus (IO1/IO2). Wire.begin() must have
    // already installed I2C port 0; reuse it so we don't double-install.
    cfg.sccb_i2c_port = 0;

    esp_err_t err = esp_camera_init(&cfg);
    if (err != ESP_OK) {
        log_e("esp_camera_init failed: 0x%02x", err);
        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (!s) { log_e("no sensor handle"); return false; }

    framesize_t target = CAM_FRAMESIZE_OV2640;
    switch (s->id.PID) {
        case OV2640_PID: s_name = "OV2640"; target = CAM_FRAMESIZE_OV2640; break;
        case OV5640_PID: s_name = "OV5640"; target = CAM_FRAMESIZE_OV5640; break;
        default:         s_name = "?";      target = CAM_FRAMESIZE_OV2640; break;
    }

    s->set_framesize(s, target);
    s->set_quality(s, CAM_JPEG_QUALITY);
    // Modest image tuning for a windshield-mounted camera.
    s->set_brightness(s, 0);
    s->set_contrast(s, 0);
    s->set_saturation(s, 0);
    s->set_gainceiling(s, GAINCEILING_4X);
    s->set_whitebal(s, 1);
    s->set_exposure_ctrl(s, 1);
    s->set_aec2(s, 1);
    s->set_vflip(s, 1);
    s->set_hmirror(s, 1);

    printSensorCaps(s);
    framesizeToWH(target, s_w, s_h);
    log_i("camera ready: %s  %ux%u", s_name, s_w, s_h);
    return true;
}

const char *sensorName() { return s_name; }
uint16_t width()  { return s_w; }
uint16_t height() { return s_h; }

}  // namespace cam
