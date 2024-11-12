/*
 * @Description: Wifi_Scan.cpp
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-16 15:19:01
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-01-12 18:45:12
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>
#include "Arduino_GFX_Library.h"
#include "pin_config.h"

#define WIFI_SSID "xinyuandianzi"
#define WIFI_PASSWORD "AA15994823428"
// #define WIFI_SSID "LilyGo-AABB"
// #define WIFI_PASSWORD "xinyuandianzi"

#define WIFI_CONNECT_WAIT_MAX 5000

#define NTP_SERVER1 "pool.ntp.org"
#define NTP_SERVER2 "time.nist.gov"
#define GMT_OFFSET_SEC 8 * 3600 // Time zone setting function, written as 8 * 3600 in East Eighth Zone (UTC/GMT+8:00)
#define DAY_LIGHT_OFFSET_SEC 0  // Fill in 3600 for daylight saving time, otherwise fill in 0

bool Wifi_Connection_Failure_Flag = false;

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

void Wifi_STA_Test(void)
{
    String text;
    int wifi_num = 0;

    gfx->fillScreen(BLACK);
    gfx->setCursor(0, 0);
    gfx->setTextSize(1);
    gfx->setTextColor(GREEN);

    Serial.println("\nScanning wifi");
    gfx->printf("Scanning wifi\n");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    wifi_num = WiFi.scanNetworks();
    if (wifi_num == 0)
    {
        text = "\nWiFi scan complete !\nNo wifi discovered.\n";
    }
    else
    {
        text = "\nWiFi scan complete !\n";
        text += wifi_num;
        text += " wifi discovered.\n\n";

        for (int i = 0; i < wifi_num; i++)
        {
            text += (i + 1);
            text += ": ";
            text += WiFi.SSID(i);
            text += " (";
            text += WiFi.RSSI(i);
            text += ")";
            text += (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " \n" : "*\n";
            delay(10);
        }
    }

    Serial.println(text);
    gfx->println(text);

    delay(3000);
    text.clear();
    gfx->fillScreen(BLACK);
    gfx->setCursor(0, 10);

    text = "Connecting to ";
    Serial.print("Connecting to ");
    gfx->printf("Connecting to\n");
    text += WIFI_SSID;
    text += "\n";

    Serial.print(WIFI_SSID);
    gfx->printf("%s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint32_t last_tick = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        gfx->printf(".");
        text += ".";
        delay(100);

        if (millis() - last_tick > WIFI_CONNECT_WAIT_MAX)
        {
            Wifi_Connection_Failure_Flag = true;
            break;
        }
    }

    if (!Wifi_Connection_Failure_Flag)
    {
        text += "\nThe connection was successful ! \nTakes ";
        Serial.print("\nThe connection was successful ! \nTakes ");
        gfx->printf("\nThe connection was successful ! \nTakes ");
        text += millis() - last_tick;
        Serial.print(millis() - last_tick);
        gfx->print(millis() - last_tick);
        text += " ms\n";
        Serial.println(" ms\n");
        gfx->printf(" ms\n");

        gfx->setTextColor(GREEN);
        gfx->printf("\nWifi test passed!");
    }
    else
    {
        gfx->setTextColor(RED);
        gfx->printf("\nWifi test error!\n");
    }
}

void PrintLocalTime(void)
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo, 10000))
    {
        Serial.println("Failed to obtain time");
        gfx->setCursor(20, 90);
        gfx->setTextColor(RED);
        gfx->print("Failed to obtain time!");
        return;
    }
    Serial.println("Get time success");
    Serial.println(&timeinfo, "%A,%B %d %Y %H:%M:%S"); // Format Output
    gfx->setCursor(30, 90);
    gfx->setTextColor(ORANGE);
    gfx->print(&timeinfo, " %Y");
    gfx->setCursor(30, 100);
    gfx->print(&timeinfo, "%B %d");
    gfx->setCursor(30, 110);
    gfx->print(&timeinfo, "%H:%M:%S");
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 2000, 8);
    ledcWrite(1, 255); // brightness 0 - 255

    gfx->begin();
    gfx->fillScreen(BLACK);

    Wifi_STA_Test();

    delay(2000);

    if (!Wifi_Connection_Failure_Flag)
    {
        // Obtain and set the time from the network time server
        // After successful acquisition, the chip will use the RTC clock to update the holding time
        configTime(GMT_OFFSET_SEC, DAY_LIGHT_OFFSET_SEC, NTP_SERVER1, NTP_SERVER2);

        delay(3000);

        PrintLocalTime();
    }
    else
    {
        gfx->setCursor(20, 100);
        gfx->setTextColor(RED);
        gfx->print("Not connected to the network");
    }
    delay(5000);
}

void loop()
{
}
