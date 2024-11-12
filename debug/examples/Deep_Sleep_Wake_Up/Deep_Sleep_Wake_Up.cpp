/*
 * @Description: ESP Sleep
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-18 15:26:31
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-02-29 08:58:32
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "pin_config.h"

#define SLEEP_ENTER_KEY KEY1
#define SLEEP_WAKE_UP_INT GPIO_NUM_0

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(SLEEP_ENTER_KEY, INPUT_PULLUP);
    pinMode(SLEEP_WAKE_UP_INT, INPUT_PULLUP);

    Serial.println("Press the button to enter deep sleep");
}

void loop()
{
    if (digitalRead(SLEEP_ENTER_KEY) == LOW)
    {
        delay(300);

        Serial.println("Enter deep sleep in 3 seconds");
        Serial.println("3");
        delay(1000);
        Serial.println("2");
        delay(1000);
        Serial.println("1");
        delay(1000);
        esp_sleep_enable_ext0_wakeup(SLEEP_WAKE_UP_INT, LOW);
        esp_deep_sleep_start();
    }
}
