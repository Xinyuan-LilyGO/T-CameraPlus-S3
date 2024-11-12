/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-09-22 17:10:10
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 14:26:30
 * @License: GPL 3.0
 */
#include <Arduino_GFX_Library.h>
#include <WiFi.h>
#include <FS.h>
#include <SD.h>
#include "esp32_audio.h"
#include "pin_config.h"

#define AUDIO_FILENAME "/44100.mp3"

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

void setup()
{
    WiFi.mode(WIFI_OFF);

    Serial.begin(115200);

    pinMode(LCD_BL, OUTPUT);
    ledcAttachPin(LCD_BL, 1); // assign TFT_BL pin to channel 1
    ledcSetup(1, 20000, 8);   // 12 kHz PWM, 8-bit resolution
    ledcWrite(1, 255);        // brightness 0 - 255

    SPI.begin(SCLK, MISO, MOSI, SD_CS); // SPI boots

    while (!gfx->begin(80000000))
    {
        Serial.println("Init display failed!");
        delay(1000);
    }
    gfx->fillScreen(BLACK);
    Serial.println("Init display successful");
    gfx->println("Init display successful");

    esp_err_t ret_val = i2s_init(I2S_NUM_0, 44100,
                                 -1 /* MCLK */, MAX98357A_BCLK /* SCLK */, MAX98357A_LRCLK /* LRCK */,
                                 MAX98357A_DOUT /* DOUT */, -1 /* DIN */);
    while (ret_val != ESP_OK)
    {
        Serial.printf("i2s_init failed: %d\n", ret_val);
        delay(1000);
    }
    i2s_zero_dma_buffer(I2S_NUM_0);
    Serial.println("Init I2S successful");
    gfx->println("Init I2S successful");

    while (!SD.begin(SD_CS, SPI, 80000000)) /* SPI bus mode */
    {
        Serial.println("ERROR: SD card mount failed!");
        gfx->println("ERROR: SD card mount failed!");
        delay(1000);
    }

    Serial.println("Init SD successful");
    gfx->println("Init SD successful");

    gfx->println("Open audio file: " AUDIO_FILENAME);
    File aFile = SD.open(AUDIO_FILENAME);
    if (!aFile || aFile.isDirectory())
    {
        Serial.println("ERROR: Failed to open " AUDIO_FILENAME " file for reading");
        gfx->println("ERROR: Failed to open " AUDIO_FILENAME " file for reading");

        return;
    }
    else
    {
        Serial.println("MP3 audio MJPEG video start");

        gfx->println("Start play audio task");
        BaseType_t ret_val = mp3_player_task_start(&aFile);
        if (ret_val != pdPASS)
        {
            Serial.printf("mp3_player_task_start failed: %d\n", ret_val);
        }
    }
}