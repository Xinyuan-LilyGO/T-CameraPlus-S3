/*
 * @Description(CN):
 *      播放Wifi音乐
 *
 * @Description(EN):
 *      Play WiFi music
 *
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-06-12 14:27:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 15:34:30
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "WiFiMulti.h"
#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"
// #include "TFT_eSPI.h"
#include "pin_config.h"

Audio audio;
// TFT_eSPI tft;
String ssid = "LilyGo-AABB";
String password = "xinyuandianzi";

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    // tft.begin();
    // tft.setRotation(3);
    // tft.fillScreen(TFT_BLACK);

    // ledcAttachPin(TFT_BL, 1); // assign TFT_BL pin to channel 1
    // ledcSetup(1, 12000, 8);   // 12 kHz PWM, 8-bit resolution
    // ledcWrite(1, 255);        // brightness 0 - 255

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    delay(2000);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi connection failed");
        // tft.println("WiFi connection failed");
        delay(1000);
    }

    Serial.println("WiFi connection successful");
    // tft.println("WiFi connection successful");

    audio.setPinout(MAX98357A_BCLK, MAX98357A_LRCLK, MAX98357A_DOUT);
    audio.setVolume(3); // 0...21,Volume setting
                        // audio.setBalance(-16);

    Serial.println("Trying to play music...");
    // tft.println("Trying to play music...");

    audio.connecttohost("http://music.163.com/song/media/outer/url?id=29747854.mp3"); // MP3
}

void loop()
{
    audio.loop();
}

// optional
void audio_info(const char *info)
{
    Serial.print("info        ");
    Serial.println(info);
    // tft.print("info        ");
    // tft.println(info);
}
void audio_id3data(const char *info)
{ // id3 metadata
    Serial.print("id3data     ");
    Serial.println(info);
}
void audio_eof_mp3(const char *info)
{ // end of file
    Serial.print("eof_mp3     ");
    Serial.println(info);
}
void audio_showstation(const char *info)
{
    Serial.print("station     ");
    Serial.println(info);
}
void audio_showstreamtitle(const char *info)
{
    Serial.print("streamtitle ");
    Serial.println(info);
}
void audio_bitrate(const char *info)
{
    Serial.print("bitrate     ");
    Serial.println(info);
}
void audio_commercial(const char *info)
{ // duration in sec
    Serial.print("commercial  ");
    Serial.println(info);
}
void audio_icyurl(const char *info)
{ // homepage
    Serial.print("icyurl      ");
    Serial.println(info);
}
void audio_lasthost(const char *info)
{ // stream URL played
    Serial.print("lasthost    ");
    Serial.println(info);
}
