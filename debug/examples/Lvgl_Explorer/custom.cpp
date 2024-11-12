/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-10-05 11:31:11
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-06 10:23:09
 * @License: GPL 3.0
 */
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "pin_config.h"

Arduino_Explorer AE_Class;

bool SD_Initialization(void)
{
    uint8_t sd_flag = 0;
    SD.end(); // Eliminate flag bits

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    while (!SD.begin(SD_CS, SPI, 80000000))
    {
        log_e("SD card initialization failed !\n");
        delay(10);
        SD.end();
        if (sd_flag == 1)
        {
            return false;
        }
        sd_flag++;
    }
    return true;
}

void Current_Directory_Print(void)
{
    String current_directory_merge;
    for (int i = 0; i < My_UI.AE_Current_Directory.size(); i++)
    {
        if (My_UI.AE_Current_Directory[i] == "/") // 判断尾部是否有文件页操作符号
        {
            current_directory_merge = My_UI.AE_Current_Directory[i];
        }
        else
        {
            current_directory_merge = current_directory_merge + "/" + My_UI.AE_Current_Directory[i];
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
    // Current_Directory_Print();
    // File_Directory_Serial_Output(folder_name, file_manager_struct);
}

/**
 * Create a demo application
 */
void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}
