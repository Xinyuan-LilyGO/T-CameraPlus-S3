/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-06 10:54:55
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 17:55:18
 * @License: GPL 3.0
 */
#pragma once

#include "gui_guider.h"
#include "Arduino_Explorer.h"
#include <map>
#include <SD.h>
#include "Audio.h"
#include "./OV2640_Camera/OV2640_Camera.h"

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

    // battery control
    enum Battery_Control_OTG
    {
        Battery_Control_OTG_OFF = 0,
        Battery_Control_OTG_ON,
    };

    // WiFi switch status
    enum WiFi_Switch_Status
    {
        WiFi_Switch_Status_OFF = 0,
        WiFi_Switch_Status_ON,
    };

    // WiFi device status
    enum WIFI_Device_Status
    {
        WIFI_Device_Status_OFF = 0,
        WIFI_Device_Status_ON,
    };

    // Camera device connect
    enum Camera_Device_Connect
    {
        Camera_Device_Connect_OFF = 0,
        Camera_Device_Connect_WIFI,
        Camera_Device_Connect_OV2640,
    };

    // Camera device status
    enum Camera_Device_Status
    {
        Camera_Device_Status_OFF = 0,
        Camera_Device_Status_ON,
    };

    // WIFI prompt flag
    enum WIFI_Prompt
    {
        WIFI_Prompt_Normal = 0,
        WIFI_Prompt_Judgment_Encrypted,
        WIFI_Prompt_Judgment_Unencrypted,
        WIFI_Prompt_Connect_Fail,
        WIFI_Prompt_Connect_Successfully,
        WIFI_Prompt_Error,
    };

    // MSM261 recording flag
    enum MSM261_Recording
    {
        MSM261_Recording_OFF = 0,
        MSM261_Recording_ON,
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

    // Camera Wifi Mode
    enum Camera_Wifi_Mode
    {
        Camera_Wifi_Mode_NULL,
        Camera_Wifi_Mode_STA,
        Camera_Wifi_Mode_SoftAP,
    };

    // wifi
    struct WIFI_Manager
    {
        String WIFI_Name;
        int32_t WIFI_Signal;
        bool WIFI_EncryptionType; // 1加密，0不加密
    };

    // Arduino_Explorer
    std::vector<String> AE_Current_Directory = {"/"};              // 文件管理文件目录寄存器（重新插拔SD卡后路径重置）
    std::vector<String> AE_Folder_Name;                            // 文件管理文件夹名暂存器（每次刷新都清空一次相当于局部变量）
    std::vector<Arduino_Explorer::File_Manager> AE_File_Manager_S; // 文件管理文件名暂存器（每次刷新都清空一次相当于局部变量）

    std::vector<lv_obj_t *> AE_LV_List_Folder; // LVGL的列表部件，的用于存放lv_obj_t *类型的文件夹地址容器（每次刷新都清空一次相当于局部变量）
    std::vector<lv_obj_t *> AE_LV_List_File;   // LVGL的列表部件，用于存放lv_obj_t *类型的文件地址容器（包括文件名和文件大小）（每次刷新都清空一次相当于局部变量）

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
    uint32_t Playing_Load_Anim_Target_Delay = 4294967295LL;        // 初始化设置最大
    uint32_t Playing_Current_Music_File_Duration = 0;              // 当前的音乐的时间
    uint32_t Playing_Current_Music_Time = 0;                       // 当前的音乐已经播放了的时间

    // playing flag
    bool Playing_Load_Anim_Delay_Flag = System_State_Of_Charge_ON_Battery_Free;

    // battery
    uint16_t Battery_Minimum_Voltage = 3200; // 电池所能掉电的最低电压
    uint8_t Battery_Voltage_Percentage = 0;  // 电测的电量百分比

    String Battery_Information_Bus_Mode = {"NULL"};
    String Battery_Information_Charge_Mode = {"NULL"};

    uint16_t Battery_Information_Total_Supply_Voltage = 0;
    uint16_t Battery_Information_Battery_Voltage = 0;
    uint16_t Battery_Information_System_Voltage = 0;

    uint16_t Battery_Information_Charge_Voltage_Limit = 0;
    uint16_t Battery_Information_Fast_Charge_Current_Limit = 0;
    uint16_t Battery_Information_Precharge_Charge_Current_Limit = 0;
    uint16_t Battery_Information_Termination_Charge_Current_Limit = 0;

    uint16_t Battery_Control_Charge_Voltage_Limit = 4208;
    uint16_t Battery_Control_Fast_Charge_Current_Limit = 320;
    uint16_t Battery_Control_Precharge_Charge_Current_Limit = 192;
    uint16_t Battery_Control_Termination_Charge_Current_Limit = 128;

    // battery flag
    bool Battery_Control_OTG_Mode_Flag = Battery_Control_OTG_OFF;
    bool Battery_Information_Refresh_Flag = false; // 只有进入电池设置模式才开始

    // wifi
    std::vector<WIFI_Manager> WIFI_Manager_C;            // WIFI容器
    std::vector<lv_obj_t *> WIFI_LV_List_Name;           // LVGL的列表部件，的用于存放lv_obj_t *类型的WIFI名字（每次刷新都清空一次相当于局部变量）
    uint8_t WiFi_Switch_Status = WiFi_Switch_Status_OFF; // WIFI开关的状态
    bool WIFI_Device_Status = WIFI_Device_Status_OFF;    // WIFI设备状态标志位
    uint32_t WIFI_Current_Number = 0;                    // 当前选中的WIFI序号

    // wifi flag
    uint8_t WIFI_Prompt_Flag = WIFI_Prompt_Normal;

    // camera flag
    uint8_t Camera_Device_Connect = Camera_Device_Connect_OFF;
    bool Camera_Device_Status = Camera_Device_Status_OFF;

    // MSM261 flag
    bool MSM261_Initialization_Flag = false;
    uint8_t MSM261_Recording_Flag = MSM261_Recording_OFF;
    String MSM261_Recording_Text = "";

    // camera wifi
    uint8_t Window_Camera_Wifi_Mode = Camera_Wifi_Mode_NULL;

    // other
    uint8_t System_Screen_Brightness = 0;
    uint8_t System_Volume = 2;

    // other flag
    bool SD_Initialization_Flag = false; // 用于检测SD卡是否插入而执行不同事件（该标志位在初始化函数里置位）
    uint8_t System_State_Of_Charge_Flag = System_State_Of_Charge_ON_Battery_Free;
    bool SY6970_Initialization_Flag = false; // 检测SY6970是否初始化成功（该标志位在初始化函数里置位）
    bool KEY1_Flag = false;
    bool KEY1_Change = false;
};

String Camera_WIFI_Test(void);
bool SD_Initialization(void);
void File_Root_Initialization(void);
void WIFI_Device_Scan(std::vector<My_Lvgl_UI::WIFI_Manager> *wifi_manager);
bool WIFI_Device_ON(void);
bool WIFI_Device_OFF(void);
bool WIFI_Connection_Encryption(const String &wifi_name, String passphrase);
bool WIFI_Connection_Unencrypted(const String &wifi_name);
void AP1511_Initialization(void);
void AP1511_Loop(void);

void My_UI_Window_StatusBar_Expand(lv_ui *ui, lv_obj_t *parent);
void My_UI_Window_StatusBar(lv_ui *ui, lv_obj_t *parent);

void custom_init(lv_ui *ui);

extern Arduino_Explorer AE_Class;
extern My_Lvgl_UI My_UI;
extern Audio audio;
