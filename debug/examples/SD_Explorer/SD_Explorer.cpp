/*
 * @Description(CN):
 *      这是一个串口模拟文件管理器 读取SD卡里内容的例程
 *
 * @Description(EN):
 *      This is an example of a serial port simulation file manager reading the content of an SD card.
 *
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-09-27 14:50:04
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 15:12:14
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "pin_config.h"
#include "Arduino_Explorer.h"

std::vector<String> current_directory = {"/"};

Arduino_Explorer AE_Class;

void Current_Directory_Print(void)
{
    String current_directory_merge;
    for (int i = 0; i < current_directory.size(); i++)
    {
        if (current_directory[i] == "/") // 判断尾部是否有文件页操作符号
        {
            current_directory_merge = current_directory[i];
        }
        else
        {
            current_directory_merge = current_directory_merge + "/" + current_directory[i];
        }
    }

    Serial.print("Current directory: ");
    Serial.println(current_directory_merge);
    Serial.println();
}

void File_Directory_Serial_Output(std::vector<String> folder_name,
                                  std::vector<Arduino_Explorer::File_Manager> file_manager)
{
    for (int i = 0; i < folder_name.size(); i++)
    {
        Serial.print("  Folder: ");
        Serial.println(folder_name[i]);
    }
    for (int i = 0; i < file_manager.size(); i++)
    {
        Serial.print("  File: ");
        Serial.print(file_manager[i].file_name);
        Serial.print("   ");
        Serial.printf("%d Kb\n", file_manager[i].file_size / 1024);
    }
    Serial.printf("\n");
}

void File_Root_Initialization(void)
{
    std::vector<String> root_directory = {"/"};
    std::vector<String> folder_name;
    std::vector<Arduino_Explorer::File_Manager> file_manager_struct;

    AE_Class.File_Directory_Refresh(&SD, root_directory, &folder_name, &file_manager_struct);
    AE_Class.File_Directory_Sort(Arduino_Explorer::File_Manager_Sort_Order, &folder_name, &file_manager_struct);
    Current_Directory_Print();
    File_Directory_Serial_Output(folder_name, file_manager_struct);
}

void setup()
{
    Serial.begin(115200);

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(PIN_SD_MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    SPI.begin(SCLK, MISO, MOSI, SD_CS); // SPI boots

    while (!SD.begin(SD_CS, SPI, 80000000))
    {
        Serial.printf("SD card initialization failed !\n");
        delay(1000);
    }

    File_Root_Initialization();
}

void loop()
{
    if (Serial.available() > 0)
    {
        char Serial_Command[100] = {0};
        std::vector<String> folder_name;
        std::vector<Arduino_Explorer::File_Manager> file_manager_s;

        Serial.read(Serial_Command, sizeof(Serial_Command));
        // Serial.write(Serial_Command,sizeof(Serial_Command));

        AE_Class.File_Directory_Refresh(&SD, current_directory, &folder_name, &file_manager_s);
        AE_Class.File_Directory_Sort(Arduino_Explorer::File_Manager_Sort_Order, &folder_name, &file_manager_s);

        if (strcmp("Folder_Return", (const char *)Serial_Command) == 0) // 文件夹返回上一级指令
        {
            folder_name.clear();
            file_manager_s.clear();
            if (current_directory.back() == "/")
            {
                Serial.printf("This directory is already a root directory and cannot be returned!\n");
            }
            else
            {
                current_directory.pop_back();
            }

            AE_Class.File_Directory_Refresh(&SD, current_directory, &folder_name, &file_manager_s);
            AE_Class.File_Directory_Sort(Arduino_Explorer::File_Manager_Sort_Order, &folder_name, &file_manager_s);
            Current_Directory_Print();
            File_Directory_Serial_Output(folder_name, file_manager_s);
        }
        else if (std::find(folder_name.begin(), folder_name.end(),
                           (const char *)Serial_Command) != folder_name.end())
        {
            folder_name.clear();
            file_manager_s.clear();

            current_directory.push_back(Serial_Command);

            AE_Class.File_Directory_Refresh(&SD, current_directory, &folder_name, &file_manager_s);
            AE_Class.File_Directory_Sort(Arduino_Explorer::File_Manager_Sort_Order, &folder_name, &file_manager_s);
            Current_Directory_Print();
            File_Directory_Serial_Output(folder_name, file_manager_s);
        }
        else
        {
            Serial.printf("Unknown Command\n");
        }
        delay(3000);
    }
}
