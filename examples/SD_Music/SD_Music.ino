/*
 * @Description(CN):
 *      SD卡播放音乐
 *
 * @Description(EN):
 *      SD Card Music Playback
 *
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-17 14:58:20
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-12 11:31:33
 * @License: GPL 3.0
 */
#include "Arduino.h"
#include "WiFiMulti.h"
#include "Audio.h"
#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "pin_config.h"

Audio audio;

File File_CurrentFile;
File File_Root;
bool File_Scan_Flag = true;

void getNextFile()
{
    String fileName;
    if (File_Scan_Flag)
    {
        File_Scan_Flag = false;
        File_Root = SD.open("/");
        if (!File_Root)
        {
            return;
        }
    }

    File_CurrentFile = File_Root.openNextFile();
    if (File_CurrentFile)
    {
        if (File_CurrentFile.isDirectory())
        {
            getNextFile(); // Recursively call to print all file names under the directory
        }
        else
        {
            fileName = File_CurrentFile.name();
            fileName.toLowerCase();
            if (fileName.indexOf(".mp3") < 0)
            {
                getNextFile(); // If the .mp3 file is less than 3, continue looking for .mp3 file
            }
        }
    }
    else
    {
        File_Scan_Flag = true;
        getNextFile(); // Returns to the previous root directory until all file searches are complete
    }
}

void playNextAudio()
{
    String sdfile;
    getNextFile();
    if (File_CurrentFile)
    {
        sdfile = File_CurrentFile.name();
        audio.connecttoSD(sdfile.c_str());
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(PIN_SD_MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    SPI.begin(SCLK, MISO, MOSI, SD_CS); // SPI boots

    SD.begin(SD_CS, SPI, 40000000);

    audio.setPinout(MAX98357A_BCLK, MAX98357A_LRCLK, MAX98357A_DOUT);
    audio.setVolume(11);   // 0...21,Volume setting
    audio.forceMono(true); // change stereo to mono
    // audio.setBalance(-16);

    playNextAudio();
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
