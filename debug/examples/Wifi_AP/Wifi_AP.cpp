/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-16 15:57:47
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 14:56:43
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include "WiFi.h"

void setup()
{
    Serial.begin(115200);
    WiFi.softAP("T-CameraPlus-S3", "88888888");
}

void loop()
{
    // if (WiFi.status() == WL_CONNECTED)
    // {
    //     Serial.print("主机名:");
    //     Serial.println(WiFi.softAPgetHostname());
    //     Serial.print("主机IP:");
    //     Serial.println(WiFi.softAPIP());
    //     Serial.print("主机IPV6:");
    //     Serial.println(WiFi.softAPIPv6());
    //     Serial.print("主机SSID:");
    //     Serial.println(WiFi.SSID());
    //     Serial.print("主机广播IP:");
    //     Serial.println(WiFi.softAPBroadcastIP());
    //     Serial.print("主机mac地址:");
    //     Serial.println(WiFi.softAPmacAddress());
    //     Serial.print("主机连接个数:");
    //     Serial.println(WiFi.softAPgetStationNum());
    //     Serial.print("主机网络ID:");
    //     Serial.println(WiFi.softAPNetworkID());
    //     Serial.print("主机状态:");
    //     Serial.println(WiFi.status());
    //     delay(1000);
    // }
}