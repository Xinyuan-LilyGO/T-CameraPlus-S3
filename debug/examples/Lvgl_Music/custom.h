/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-10-06 10:54:55
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-16 11:08:11
 * @License: GPL 3.0
 */
#pragma once

#include "gui_guider.h"
#include "Arduino_Explorer.h"
#include <map>
#include <SD.h>
#include "Audio.h"

class My_Lvgl_UI
{
public:
    // my music scan prompt flag
    enum Playing_Current_Static
    {
        Playing_Current_Static_Playing = 0,
        Playing_Current_Static_Pause,
        Playing_Current_Static_Switch,
    };

    // my music scan prompt flag
    enum Music_Scan_Prompt
    {
        Music_Scan_Prompt_Normal = 0,
        Music_Scan_Prompt_Success,
        Music_Scan_Prompt_Fail,
        Music_Scan_Prompt_Error,
    };

    // my music scan prompt flag
    enum Music_List_Prompt
    {
        Music_List_Prompt_Normal = 0,
        Music_List_Prompt_Play_Music_Judgment,
        Music_List_Prompt_Play_Music_Fail,
        Music_List_Prompt_Error,
    };

    // playing load anim delay flag
    enum Playing_Load_Anim_Delay
    {
        Playing_Load_Anim_Delay_OFF = 0,
        Playing_Load_Anim_Delay_ON,
    };

    // system state of charge flag
    enum System_State_Of_Charge
    {
        System_State_Of_Charge_ON_Battery_Free = 0,
        System_State_Of_Charge_ON_Battery_Level_1,
        System_State_Of_Charge_ON_Battery_Level_2,
        System_State_Of_Charge_ON_Battery_Level_3,
        System_State_Of_Charge_OFF_Battery_Level_1,
        System_State_Of_Charge_OFF_Battery_Level_2,
        System_State_Of_Charge_OFF_Battery_Level_3,
        System_State_Of_Charge_ON_Battery_Full,
        System_State_Of_Charge_OFF_Battery_Full,
    };

    // Arduino_Explorer
    std::vector<String> AE_Current_Directory = {"/"};              // 文件管理文件目录寄存器（重新插拔SD卡后路径重置）
    std::vector<String> AE_Folder_Name;                            // 文件管理文件夹名暂存器（每次刷新都清空一次相当于局部变量）
    std::vector<Arduino_Explorer::File_Manager> AE_File_Manager_S; // 文件管理文件名暂存器（每次刷新都清空一次相当于局部变量）

    std::vector<lv_obj_t *> AE_LV_List_Folder; // LVGL的列表部件，的用于存放lv_obj_t *类型的文件夹地址容器（每次刷新都清空一次相当于局部变量）
    std::vector<lv_obj_t *> AE_LV_List_File;   // LVGL的列表部件，用于存放lv_obj_t *类型的文件地址容器（包括文件名和文件大小）（每次刷新都清空一次相当于局部变量）

    // file flag
    bool AE_SD_Mode_Flag = false; // 用于检测SD卡是否插入而执行不同事件

    // music scan
    std::vector<String> Music_Scan_Directory = {"/"}; // 音乐扫描文件目录寄存器（重新插拔SD卡后路径重置）

    // music scan flag
    uint8_t Music_Scan_Prompt_Flag = 0;

    // music list
    String Music_List_Directory = {"/"};                         // 音乐列表音乐文件目录容器（每次搜索音乐文件后更新）
    std::vector<Arduino_Explorer::File_Manager> Music_List_File; // 音乐列表音乐文件容器
    uint64_t Music_List_Total_Number = 0;                        // 音乐列表总歌曲数量
    long long Music_List_Current_Number = 0;                     // 音乐列表中选定的音乐文件序号

    // music list flag
    uint8_t Music_List_Prompt_Flag = 0;

    // playing
    // uint64_t Playing_Current_Number = 0;
    String Playing_Current_Music_Name = {"NULL"};                  // 当前音乐播放的名字
    uint8_t Playing_Current_Static = Playing_Current_Static_Pause; // 当前音乐播放状态
    uint8_t Playing_Music_Volume = 2;
    uint32_t Playing_Load_Anim_Target_Delay = 4294967295LL; // 初始化设置最大
    uint32_t Playing_Current_Music_File_Duration = 0;       // 当前的音乐的时间
    uint32_t Playing_Current_Music_Time = 0;                // 当前的音乐已经播放了的时间

    // playing flag
    bool Playing_Load_Anim_Delay_Flag = System_State_Of_Charge_ON_Battery_Free;

    // other
    uint8_t System_Screen_Brightness = 255;

    // other flag
    uint8_t System_State_Of_Charge_Flag = System_State_Of_Charge_ON_Battery_Free;
};

bool SD_Initialization(void);
void File_Root_Initialization(void);

void custom_init(lv_ui *ui);

extern Arduino_Explorer AE_Class;
extern My_Lvgl_UI My_UI;
extern Audio audio;
