/*
 * @Description: TFT.cpp
 * @version: v1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-06-05 13:01:59
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-12 11:32:26
 */
#include <Arduino.h>
#include "TFT_eSPI.h"
#include "material.h"
#include "pin_config.h"

TFT_eSPI tft;

void image()
{
    tft.pushImage(0, 0, 240, 240, (uint16_t *)gImage_1);
    delay(2000);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    tft.begin();

    tft.setRotation(0);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);

    ledcSetup(0, 20000, 8);
    ledcAttachPin(LCD_BL, 0);
    ledcWrite(0, 255);

    image();
}

void loop()
{
    // tft.println("Ciallo");
    // delay(1000);
}
