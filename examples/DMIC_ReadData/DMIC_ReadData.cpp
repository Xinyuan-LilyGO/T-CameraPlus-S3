/*
 * @Description: DMIC_ReadData.cpp
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-17 16:24:06
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-12 11:29:27
 * @License: GPL 3.0
 */

#include "DFrobot_MSM261.h"
#include "pin_config.h"

#define MICROPHONE_SAMPLE_RATE 96000 // 采样速率
#define MICROPHONE_DATA_BIT 16       // 数据位数

DFRobot_Microphone microphone(MSM261_BCLK, MSM261_WS, MSM261_DIN);
char i2sReadrawBuff[100];
void setup()
{
    Serial.begin(115200);

    while (microphone.begin(MICROPHONE_SAMPLE_RATE, MICROPHONE_DATA_BIT) != 0)
    {
        Serial.println(" I2S init failed");
    }
    Serial.println("I2S init success");
}

void loop()
{
    microphone.read(i2sReadrawBuff, 100);
    // 输出右声道数据
    Serial.println("right:");
    Serial.println((int16_t)(i2sReadrawBuff[2] | i2sReadrawBuff[3] << 8));
    Serial.println();

    // 输出左声道数据
    Serial.println("left:");
    Serial.println((int16_t)(i2sReadrawBuff[0] | i2sReadrawBuff[1] << 8));
    Serial.println();
    delay(100);
}
