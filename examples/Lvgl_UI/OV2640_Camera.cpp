/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-18 17:31:49
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-20 14:01:17
 * @License: GPL 3.0
 */
#include <WiFi.h>
#include "custom.h"
#include "pin_config.h"
#include <esp_camera.h>
#include "app_httpd.tpp"
#include "OV2640_Camera.h"
#include "Arduino_GFX_Library.h"

extern Arduino_GFX *gfx;

bool OV2640_Initialization(OV2640_Pixel_Format pixel_format)
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_HQVGA;
    config.pixel_format = (pixformat_t)pixel_format; // for streaming PIXFORMAT_JPEG
    // config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 2;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);

        My_UI.Camera_Device_Status = My_UI.Camera_Device_Status_OFF;
        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);       // flip it back
        s->set_brightness(s, 1);  // up the brightness just a bit
        s->set_saturation(s, -2); // lower the saturation
    }

    My_UI.Camera_Device_Status = My_UI.Camera_Device_Status_ON;
    return true;
}

void OV2640_Loop(void)
{
    lv_obj_t *act_scr = lv_scr_act();

    if (act_scr->user_data == "Camera_Screen")
    {
        if (My_UI.Camera_Device_Status == My_UI.Camera_Device_Status_ON)
        {
            camera_fb_t *frame = esp_camera_fb_get();
            if (frame)
            {
                gfx->draw16bitBeRGBBitmap(0, 24, (uint16_t *)frame->buf, frame->width, frame->height);
                esp_camera_fb_return(frame);
            }
            lv_obj_update_layout(lv_scr_act());
        }
    }
}
