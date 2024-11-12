/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-08-22 11:49:06
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-22 11:51:30
 * @License: GPL 3.0
 */
#include <Arduino.h>

void setup(void)
{
    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);
}

void loop(void)
{
    digitalWrite(47, HIGH);
    delay(1000);
    digitalWrite(47, LOW);
    delay(1000);
}