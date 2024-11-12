/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-06-21 18:42:16
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-12 17:02:20
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "pin_config.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");
}

void loop()
{
    // Gets the number of bytes (characters) that can be used to read from the serial port
    // This is the data that has arrived and is stored in the serial receive buffer (containing 64 bytes)
    if (Serial.available() > 0)
    {
        Serial.printf("%c",Serial.read());
    }

}
