//  SPDX-License-Identifier: MIT
//  Copyright 2020-2023 NXP
#pragma once

#include "gui_guider.h"
#include "Arduino_Explorer.h"
#include <SD.h>

class My_Lvgl_UI
{
public:
    // file management
    std::vector<String> AE_Current_Directory = {"/"};
    std::vector<String> AE_Folder_Name;
    std::vector<Arduino_Explorer::File_Manager> AE_File_Manager_S;
    std::vector<lv_obj_t *> Explorer_list_1_folder;
    std::vector<lv_obj_t *> Explorer_list_1_file;

    // file flag
    bool AE_SD_Mode_Flag = false;//用于检测SD卡是否插入而执行不同事件
};

bool SD_Initialization(void);
void File_Root_Initialization(void);

void custom_init(lv_ui *ui);

extern Arduino_Explorer AE_Class;
extern My_Lvgl_UI My_UI;
