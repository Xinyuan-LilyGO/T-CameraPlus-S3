/*
 * @Description: Sleep
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2024-03-11 10:05:32
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-01-24 11:30:40
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "pin_config.h"
#include "Arduino_GFX_Library.h"
#include "Arduino_DriveBus_Library.h"

#define SLEEP_WAKE_UP_INT GPIO_NUM_17

bool Touch_Int_Flag = false;

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(SLEEP_WAKE_UP_INT, INPUT_PULLUP);

    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 2000, 8);
    ledcWrite(1, 0); // brightness 0 - 255

    attachInterrupt(
        SLEEP_WAKE_UP_INT,
        []
        {
            Touch_Int_Flag = true;
        },
        FALLING);

    gfx->begin();

    gfx->fillScreen(WHITE);
    gfx->setTextSize(2);
    gfx->setTextColor(RED);
    gfx->setCursor(10, LCD_HEIGHT / 2 - 20);
    gfx->print("Press the KEY1 switch to turn the device on or off.");

    for (int i = 0; i <= 255; i++)
    {
        ledcWrite(1, i);
        delay(2);
    }
    delay(1000);
}

void loop()
{
    if (Touch_Int_Flag == true)
    {
        for (int i = 255; i >= 0; i--)
        {
            ledcWrite(1, i);
            delay(5);
        }

        delay(1000);
        Touch_Int_Flag = false;
        Serial.println("Enter deep sleep");
        // gpio_hold_en(SLEEP_WAKE_UP_INT);
        esp_sleep_enable_ext0_wakeup(SLEEP_WAKE_UP_INT, LOW);
        esp_deep_sleep_start();
    }
}
