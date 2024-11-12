/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-14 16:16:07
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-16 15:11:59
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"

uint8_t i = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(SD_CS,OUTPUT);
    pinMode(SCLK,OUTPUT);
    pinMode(MOSI,OUTPUT);
    pinMode(MISO,OUTPUT);

    digitalWrite(SD_CS, i);
    digitalWrite(SCLK, i);
    digitalWrite(MOSI, i);
    digitalWrite(MISO, i);
}

void loop()
{
    digitalWrite(SD_CS, i);
    digitalWrite(SCLK, i);
    digitalWrite(MOSI, i);
    digitalWrite(MISO, i);
    i = !i;
    Serial.print("Ciallo\n");
    delay(1000);
}