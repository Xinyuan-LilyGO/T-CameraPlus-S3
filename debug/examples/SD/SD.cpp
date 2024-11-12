/*
 * @Description(EN):
 *      T-Display-S3-Expansion_board SD card test procedure.
 *      For pin connections, see "pin_config.h" file.
 * 
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-06-12 18:33:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 15:04:17
 * @License: GPL 3.0
 */
#include <SPI.h>
#include <SD.h>
#include "TFT_eSPI.h"
#include "pin_config.h"

TFT_eSPI tft;
File testFile;

bool SelfLocking_Flag = false;

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo T-CameraPlus-S3");

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    SPI.begin(SCLK, MISO, MOSI, SD_CS); // SPI boots

    // tft.begin();
    // tft.setRotation(3);
    // // tft.setSwapBytes(true); // Make the picture color by RGB->BGRs
    // tft.fillScreen(TFT_BLACK);

    // ledcAttachPin(TFT_BL, 1); // assign TFT_BL pin to channel 1
    // ledcSetup(1, 12000, 8);   // 12 kHz PWM, 8-bit resolution
    // ledcWrite(1, 255);        // brightness 0 - 255

    // testFile = SD.open("test.txt", FILE_READ);
    // if (testFile)
    // {
    //     tft.drawString("test.txt:", 0, 0, 4);
    //     while (testFile.available())
    //     {
    //         tft.drawChar((int16_t)testFile.read(), 0, 0, 4);
    //     }
    //     testFile.close();
    // }
}

void loop()
{
    uint8_t cardType = 0;
    uint64_t cardSize = 0;
    uint8_t numSectors = 0;

    if (!SD.begin(SD_CS, SPI, 80000000)) // SD boots
    {
        SelfLocking_Flag = false;

        tft.fillScreen(TFT_BLACK);
        tft.drawString("Detecting SD card", 0, 20, 2);
        Serial.println("Detecting SD card");

        tft.setTextColor(TFT_BROWN);
        tft.drawString("LILYGO", 20, 110, 4);
        tft.drawString("|---SD_Dirver---| V1.0.0", 70, 130, 2);
        tft.setTextColor(TFT_WHITE);

        tft.drawString("SD card initialization failed !", 0, 0, 2);
        Serial.println("SD card initialization failed !");

        delay(100);
        tft.drawString(".", 120, 20, 2);
        Serial.println(".");
        delay(100);
        tft.drawString(".", 125, 20, 2);
        Serial.println(".");
        delay(100);
        tft.drawString(".", 130, 20, 2);
        Serial.println(".");
        delay(100);
        tft.drawString(".", 135, 20, 2);
        Serial.println(".");
        delay(100);
        tft.drawString(".", 140, 20, 2);
        Serial.println(".");
        delay(100);
        tft.drawString(".", 145, 20, 2);
        Serial.println(".");
        delay(100);
    }
    else
    {
        delay(50); // Wait for the SD card

        if (SelfLocking_Flag == false)
        {
            SelfLocking_Flag = true;
            delay(50);
            tft.fillScreen(TFT_BLACK);
        }

        tft.drawString("SD card initialization successful !", 0, 0, 2);
        Serial.println("SD card initialization successful !");

        tft.setTextColor(TFT_BROWN);
        tft.drawString("LILYGO", 20, 110, 4);
        tft.drawString("|---SD_Dirver---| V1.0.0", 70, 130, 2);
        tft.setTextColor(TFT_WHITE);

        cardType = SD.cardType();
        cardSize = SD.cardSize() / (1024 * 1024);
        numSectors = SD.numSectors();
        switch (cardType)
        {
        case CARD_NONE:
            Serial.println("No SD card attached");
            tft.drawString("No SD card attached", 0, 20, 2);
            break;
        case CARD_MMC:
            Serial.print("SD Card Type: ");
            tft.drawString("SD Card Type:  ", 0, 20, 2);

            Serial.println("MMC");
            tft.drawString("MMC        ", 100, 20, 2);

            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            tft.drawString("SD Card Size:", 0, 40, 2);
            tft.drawNumber(cardSize, 100, 40, 2);
            tft.drawString("MB", 150, 40, 2);
            tft.drawString("Number of SD card partitions:", 0, 60, 2);
            tft.drawNumber(numSectors, 190, 60, 2);
            break;
        case CARD_SD:
            Serial.print("SD Card Type: ");
            tft.drawString("SD Card Type:  ", 0, 20, 2);

            Serial.println("SDSC");
            tft.drawString("SDSC        ", 100, 20, 2);

            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            tft.drawString("SD Card Size:", 0, 40, 2);
            tft.drawNumber(cardSize, 100, 40, 2);
            tft.drawString("MB", 150, 40, 2);
            tft.drawString("Number of SD card partitions:", 0, 60, 2);
            tft.drawNumber(numSectors, 190, 60, 2);
            break;
        case CARD_SDHC:
            Serial.print("SD Card Type: ");
            tft.drawString("SD Card Type:  ", 0, 20, 2);

            Serial.println("SDHC");
            tft.drawString("SDHC        ", 100, 20, 2);

            Serial.printf("SD Card Size: %lluMB\n", cardSize);
            tft.drawString("SD Card Size:", 0, 40, 2);
            tft.drawNumber(cardSize, 100, 40, 2);
            tft.drawString("MB", 150, 40, 2);
            tft.drawString("Number of SD card partitions:", 0, 60, 2);
            tft.drawNumber(numSectors, 190, 60, 2);
            break;
        default:
            Serial.println("UNKNOWN");
            tft.drawString("UNKNOWN", 100, 40, 2);
            break;
        }
    }
    SD.end();
}