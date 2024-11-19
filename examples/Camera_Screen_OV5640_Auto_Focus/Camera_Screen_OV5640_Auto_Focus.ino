/*
 * @Description(CN):
 *       这是一个将OV2640摄像头数据投影到屏幕上的例程
 *
 * @Description(EN):
 *      This is a routine that projects the OV2640 camera data onto the T-CameraPlus-S3 screen.
 *
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-11-15 16:57:21
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2024-11-19 18:28:30
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "Arduino_GFX_Library.h"
#include "pin_config.h"
#include <esp_camera.h>
#include "camera_index.h"
#include "app_httpd.tpp"
#include "ESP32_OV5640_AF.h"

static bool Camera_Initialization_Flag = false;

size_t CycleTime = 0;

OV5640 ov5640 = OV5640();

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_TFT *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

bool Camera_Initialization(void)
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
    config.frame_size = FRAMESIZE_240X240;
    // config.pixel_format = PIXFORMAT_JPEG; // for streaming
    config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 0;
    config.fb_count = 2;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        gfx->printf("Camera init failed with error 0x%x \n", err);

        return false;
    }

    sensor_t *s = esp_camera_sensor_get();
    if (s)
    {
        Serial.print("camera id:");
        Serial.println(s->id.PID);
        gfx->print("camera id:");
        gfx->println(s->id.PID);
        gfx->println();
        camera_sensor_info_t *sinfo = esp_camera_sensor_get_info(&(s->id));
        if (sinfo)
        {
            Serial.print("camera model:");
            Serial.println(sinfo->name);
            gfx->print("camera model:");
            gfx->println(sinfo->name);
            gfx->println();
        }
    }
    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID)
    {
        s->set_vflip(s, 1);       // flip it back
        s->set_brightness(s, 1);  // up the brightness just a bit
        s->set_saturation(s, -2); // lower the saturation
    }

    if (s->id.PID == OV5640_PID)
    {
        s->set_vflip(s, 1);   // 上下翻转
        s->set_hmirror(s, 0); // 镜像翻转
    }

    return true;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(LCD_BL, OUTPUT);
    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, 255); // brightness 0 - 255

    gfx->begin();
    gfx->fillScreen(WHITE);

    gfx->setTextColor(BLACK);

    if (Camera_Initialization() == true)
    {
        Camera_Initialization_Flag = true;
        sensor_t *sensor = esp_camera_sensor_get();
        ov5640.start(sensor);

        if (ov5640.focusInit() == 0)
        {
            Serial.println("OV5640_Focus_Init Successful!");
        }
        else
        {
            Serial.println("OV5640_Focus_Init Failed!");
        }

        if (ov5640.autoFocusMode() == 0)
        {
            Serial.println("OV5640_Auto_Focus Successful!");
        }
        else
        {
            Serial.println("OV5640_Auto_Focus Failed!");
        }
    }
    else
    {
        Camera_Initialization_Flag = false;
    }
}

void loop()
{
    if (millis() > CycleTime)
    {
        ov5640.Focus_Test();
        CycleTime = millis() + 5000;
    }

    if (Camera_Initialization_Flag == true)
    {
        uint8_t rc = ov5640.getFWStatus();
        Serial.printf("FW_STATUS = 0x%x\n", rc);

        if (rc == -1)
        {
            Serial.println("Check your OV5640");
        }
        else if (rc == FW_STATUS_S_FOCUSED)
        {
            Serial.println("Focused!");
        }
        else if (rc == FW_STATUS_S_FOCUSING)
        {
            Serial.println("Focusing!");
        }
        else
        {
        }

        camera_fb_t *frame = esp_camera_fb_get();
        if (frame)
        {
            gfx->draw16bitBeRGBBitmap(0, 0, (uint16_t *)frame->buf, frame->width, frame->height);
            esp_camera_fb_return(frame);
        }

        delay(1);
    }
}