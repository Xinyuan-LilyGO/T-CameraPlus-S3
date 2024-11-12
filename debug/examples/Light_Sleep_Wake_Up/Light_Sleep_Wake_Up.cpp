/*
 * @Description: ESP Sleep
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-18 15:26:31
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-03-30 11:35:37
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "pin_config.h"

#define SLEEP_ENTER_KEY KEY1
#define SLEEP_WAKE_UP_INT GPIO_NUM_0

static size_t CycleTime = 0;
static bool Light_Sleep_Exit_Initialization_Flag = false;
static bool Light_Sleep_Exit_Flag = false;

void setup()
{
    // 使用浅睡眠功能建议将串口配置为UART0而不是USB
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(SLEEP_ENTER_KEY, INPUT_PULLUP);
    pinMode(SLEEP_WAKE_UP_INT, INPUT_PULLUP);

    Serial.println("Press the button to enter light sleep");
}

void loop()
{
    if (digitalRead(SLEEP_ENTER_KEY) == LOW)
    {
        delay(300);

        Serial.println("Enter light sleep in 3 seconds");
        Serial.println("3");
        delay(1000);
        Serial.println("2");
        delay(1000);
        Serial.println("1");
        delay(1000);

        Light_Sleep_Exit_Initialization_Flag = true;

        esp_sleep_enable_ext0_wakeup(SLEEP_WAKE_UP_INT, LOW);
        esp_light_sleep_start();
    }

    if (Light_Sleep_Exit_Initialization_Flag == true)
    {
        // 浅睡眠过后使用串口工具查看信息
        Light_Sleep_Exit_Initialization_Flag = false;
        Light_Sleep_Exit_Flag = true;
    }

    if (Light_Sleep_Exit_Flag == true)
    {
        if (millis() > CycleTime)
        {
            Serial.println("Successfully exited light sleep");
            CycleTime = millis() + 1000;
        }
    }
}
