/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-05 11:31:11
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-06 17:13:26
 * @License: GPL 3.0
 */
#include <stdio.h>
#include "lvgl.h"
#include "widgets_init.h"
#include "custom.h"
#include "pin_config.h"

#define WIFI_SSID "xinyuandianzi"
#define WIFI_PASSWORD "AA15994823428"
// #define WIFI_SSID "LilyGo-AABB"
// #define WIFI_PASSWORD "xinyuandianzi"

#define WIFI_SOFTAP_SSID "T-CameraPlus-S3"
#define WIFI_SOFTAP_PASSWORD "88888888"

#define WIFI_CONNECT_WAIT_MAX 5000

int Window_StatusBar_digital_clock_1_hour_value = 00;
int Window_StatusBar_digital_clock_1_min_value = 00;
int Window_StatusBar_digital_clock_1_sec_value = 00;

Arduino_Explorer AE_Class;

String Camera_WIFI_Test(void)
{
    String text;
    int wifi_num = 0;
    uint64_t last_tick;

    switch (My_UI.Window_Camera_Wifi_Mode)
    {
    case My_UI.Camera_Wifi_Mode::Camera_Wifi_Mode_STA:
        text = "\n\n\nScanning wifi";
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);

        wifi_num = WiFi.scanNetworks();
        if (wifi_num == 0)
        {
            text += "\nWiFi scan complete !\nNo wifi discovered.\n";
        }
        else
        {
            text += "\nWiFi scan complete !\n";
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

        text += "Connecting to ";
        text += WIFI_SSID;
        text += "\n";

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        last_tick = millis();

        while (WiFi.status() != WL_CONNECTED)
        {
            text += ".";

            if (millis() - last_tick > WIFI_CONNECT_WAIT_MAX)
            {
                My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_OFF;
                break;
            }
            else
            {
                My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_ON;
            }
            delay(500); // 这个延时必须要有
        }

        if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
        {
            text += "\nThe connection was successful ! \nTakes ";
            text += (String)(millis() - last_tick);
            text += " ms\n";
        }
        else
        {
            text += "\nThe connection was fail ! \nTakes ";
        }

        return text;
        break;
    case My_UI.Camera_Wifi_Mode::Camera_Wifi_Mode_SoftAP:
        text = "\n\n\nStart SoftAP\n";

        WiFi.softAP(WIFI_SOFTAP_SSID, WIFI_SOFTAP_PASSWORD);

        My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_ON;

        text += "\nThe SoftAP initialization was successful !";

        text += "\n\nSSID:";
        text += WIFI_SOFTAP_SSID;
        text += "\nPASSWPRD:";
        text += WIFI_SOFTAP_PASSWORD;

        return text;
        break;

    default:
        return "WIFI initialization failed";
        break;
    }

    return "WIFI initialization failed";
}

void AP1511_Initialization(void)
{
    pinMode(AP1511B_FBC, OUTPUT);
    digitalWrite(AP1511B_FBC, LOW);

    attachInterrupt(
        KEY1,
        []
        {
            My_UI.KEY1_Change = true;
            My_UI.KEY1_Flag = !My_UI.KEY1_Flag;
        },
        FALLING); // Triggered every 1ms
}

void AP1511_Loop(void)
{
    if (My_UI.KEY1_Change == true)
    {
        My_UI.KEY1_Change = false;
        if (My_UI.KEY1_Flag == true)
        {
            digitalWrite(AP1511B_FBC, HIGH);
        }
        if (My_UI.KEY1_Flag == false)
        {
            digitalWrite(AP1511B_FBC, LOW);
        }
        delay(500);
    }
}

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
            My_UI.SD_Initialization_Flag = false;
            return false;
        }
        sd_flag++;
    }

    My_UI.SD_Initialization_Flag = true;
    return true;
}

void WIFI_Device_Scan(std::vector<My_Lvgl_UI::WIFI_Manager> *wifi_manager)
{
    My_Lvgl_UI::WIFI_Manager wifi_manager_temp; // wifi结构体暂存器
    int16_t wifi_total_number = 0;

    wifi_total_number = WiFi.scanNetworks();

    for (int16_t i = 0; i < wifi_total_number; i++)
    {
        wifi_manager_temp.WIFI_Name = WiFi.SSID(i);
        wifi_manager_temp.WIFI_Signal = WiFi.RSSI(i);
        wifi_manager_temp.WIFI_EncryptionType = (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? 0 : 1;
        wifi_manager->push_back(wifi_manager_temp);
    }
}

bool WIFI_Device_ON(void)
{
    if (WiFi.mode(WIFI_STA) == false)
    {
        My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_OFF;
        return false;
    }

    if (WiFi.disconnect(false) == false)
    {
        My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_OFF;
        return false;
    }
    delay(100);

    My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_ON;
    return true;
}

bool WIFI_Device_OFF(void)
{
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    delay(100);

    My_UI.WIFI_Device_Status = My_UI.WIFI_Device_Status_OFF;

    return true;
}

bool WIFI_Connection_Encryption(const String &wifi_name, String passphrase)
{
    uint8_t wifi_flag = 0;

    WiFi.begin(wifi_name.c_str(), passphrase);

    while (WiFi.status() != WL_CONNECTED)
    {
        wifi_flag++;
        if (wifi_flag >= 50) // 5秒
        {
            return false;
        }
        delay(100);
    }

    return true;
}

bool WIFI_Connection_Unencrypted(const String &wifi_name)
{
    uint8_t wifi_flag = 0;

    WiFi.begin(wifi_name);

    while (WiFi.status() != WL_CONNECTED)
    {
        wifi_flag++;
        if (wifi_flag >= 50) // 5秒
        {
            return false;
        }
        delay(100);
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
 * @brief 全窗口状态栏展开显示
 * @param *ui
 * @param *parent
 * @return
 * @Date 2023-10-16 13:33:03
 */
void My_UI_Window_StatusBar_Expand(lv_ui *ui, lv_obj_t *parent)
{
    // Write codes Window_StatusBar_Expand_cont_2
    ui->Window_StatusBar_Expand_cont_2 = lv_obj_create(parent);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_cont_2, 0, -2);
    lv_obj_set_size(ui->Window_StatusBar_Expand_cont_2, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_cont_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);

    // Write style for Window_StatusBar_Expand_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_cont_2, 231, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_cont_2, lv_color_hex(0x2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Window_StatusBar_Expand_slider_1
    ui->Window_StatusBar_Expand_slider_1 = lv_slider_create(ui->Window_StatusBar_Expand_cont_2);
    lv_slider_set_range(ui->Window_StatusBar_Expand_slider_1, 0, 21);
    lv_slider_set_value(ui->Window_StatusBar_Expand_slider_1, My_UI.System_Volume, lv_anim_enable_t::LV_ANIM_OFF);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_slider_1, 60, 140);
    lv_obj_set_size(ui->Window_StatusBar_Expand_slider_1, 165, 10);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_slider_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_1, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Window_StatusBar_Expand_slider_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_slider_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_1, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_1, 50, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes Window_StatusBar_Expand_imgbtn_4
    ui->Window_StatusBar_Expand_imgbtn_4 = lv_imgbtn_create(ui->Window_StatusBar_Expand_cont_2);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, &_16_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, &_18_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_20_alpha_50x50, NULL);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->Window_StatusBar_Expand_imgbtn_4_label = lv_label_create(ui->Window_StatusBar_Expand_imgbtn_4);
    lv_label_set_text(ui->Window_StatusBar_Expand_imgbtn_4_label, "");
    lv_label_set_long_mode(ui->Window_StatusBar_Expand_imgbtn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Window_StatusBar_Expand_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Window_StatusBar_Expand_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_imgbtn_4, 20, 20);
    lv_obj_set_size(ui->Window_StatusBar_Expand_imgbtn_4, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_imgbtn_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_Expand_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Window_StatusBar_Expand_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_ON)
    {
        lv_imgbtn_set_state(ui->Window_StatusBar_Expand_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED); // 开
    }

    if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_OFF)
    {
        lv_imgbtn_set_state(ui->Window_StatusBar_Expand_imgbtn_4, LV_IMGBTN_STATE_RELEASED); // 关
    }

    // Write codes Window_StatusBar_Expand_slider_2
    ui->Window_StatusBar_Expand_slider_2 = lv_slider_create(ui->Window_StatusBar_Expand_cont_2);
    lv_slider_set_range(ui->Window_StatusBar_Expand_slider_2, 0, 255);
    lv_slider_set_value(ui->Window_StatusBar_Expand_slider_2, My_UI.System_Screen_Brightness, lv_anim_enable_t::LV_ANIM_OFF);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_slider_2, 60, 95);
    lv_obj_set_size(ui->Window_StatusBar_Expand_slider_2, 165, 10);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_slider_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_2, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_2, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_2, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Window_StatusBar_Expand_slider_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_slider_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_2, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_Expand_slider_2, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_Expand_slider_2, lv_color_hex(0x2195f6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_Expand_slider_2, 50, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes Window_StatusBar_Expand_imgbtn_5
    ui->Window_StatusBar_Expand_imgbtn_5 = lv_imgbtn_create(ui->Window_StatusBar_Expand_cont_2);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, &_17_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, &_19_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_21_alpha_50x50, NULL);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui->Window_StatusBar_Expand_imgbtn_5_label = lv_label_create(ui->Window_StatusBar_Expand_imgbtn_5);
    lv_label_set_text(ui->Window_StatusBar_Expand_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->Window_StatusBar_Expand_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Window_StatusBar_Expand_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Window_StatusBar_Expand_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_imgbtn_5, 100, 20);
    lv_obj_set_size(ui->Window_StatusBar_Expand_imgbtn_5, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_imgbtn_5, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_Expand_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Window_StatusBar_Expand_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Window_StatusBar_Expand_imgbtn_6
    ui->Window_StatusBar_Expand_imgbtn_6 = lv_imgbtn_create(ui->Window_StatusBar_Expand_cont_2);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, &_22_alpha_30x30, NULL);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    ui->Window_StatusBar_Expand_imgbtn_6_label = lv_label_create(ui->Window_StatusBar_Expand_imgbtn_6);
    lv_label_set_text(ui->Window_StatusBar_Expand_imgbtn_6_label, "");
    lv_label_set_long_mode(ui->Window_StatusBar_Expand_imgbtn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Window_StatusBar_Expand_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Window_StatusBar_Expand_imgbtn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_imgbtn_6, 17, 85);
    lv_obj_set_size(ui->Window_StatusBar_Expand_imgbtn_6, 30, 30);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_imgbtn_6, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_Expand_imgbtn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Window_StatusBar_Expand_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Window_StatusBar_Expand_imgbtn_7
    ui->Window_StatusBar_Expand_imgbtn_7 = lv_imgbtn_create(ui->Window_StatusBar_Expand_cont_2);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_7, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Window_StatusBar_Expand_imgbtn_7, LV_IMGBTN_STATE_RELEASED, NULL, &_23_alpha_27x27, NULL);
    lv_obj_add_flag(ui->Window_StatusBar_Expand_imgbtn_7, LV_OBJ_FLAG_CHECKABLE);
    ui->Window_StatusBar_Expand_imgbtn_7_label = lv_label_create(ui->Window_StatusBar_Expand_imgbtn_7);
    lv_label_set_text(ui->Window_StatusBar_Expand_imgbtn_7_label, "");
    lv_label_set_long_mode(ui->Window_StatusBar_Expand_imgbtn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Window_StatusBar_Expand_imgbtn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Window_StatusBar_Expand_imgbtn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Window_StatusBar_Expand_imgbtn_7, 19, 130);
    lv_obj_set_size(ui->Window_StatusBar_Expand_imgbtn_7, 27, 27);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_Expand_imgbtn_7, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_Expand_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_Expand_imgbtn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Window_StatusBar_Expand_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Window_StatusBar_Expand_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Window_StatusBar_Expand_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Window_StatusBar_Expand_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Window_StatusBar_Expand_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_Expand_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_CHECKED);
}

/**
 * @brief 全窗口状态栏显示
 * @param *ui
 * @param *parent
 * @return
 * @Date 2023-10-16 13:33:53
 */
void My_UI_Window_StatusBar(lv_ui *ui, lv_obj_t *parent)
{
    // Write codes Window_StatusBar_cont_1
    ui->Window_StatusBar_cont_1 = lv_obj_create(parent);
    lv_obj_set_pos(ui->Window_StatusBar_cont_1, 0, 0);
    lv_obj_set_size(ui->Window_StatusBar_cont_1, 240, 21);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Window_StatusBar_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Window_StatusBar_digital_clock_1
    static bool Window_StatusBar_digital_clock_1_timer_enabled = false;
    ui->Window_StatusBar_digital_clock_1 = lv_dclock_create(ui->Window_StatusBar_cont_1, "00:00:00");
    lv_dclock_set_text_fmt(guider_ui.Window_StatusBar_digital_clock_1,
                           "%02d:%02d:%02d", Window_StatusBar_digital_clock_1_hour_value,
                           Window_StatusBar_digital_clock_1_min_value,
                           Window_StatusBar_digital_clock_1_sec_value);

    if (!Window_StatusBar_digital_clock_1_timer_enabled)
    {
        lv_timer_create(Window_StatusBar_digital_clock_1_timer, 1000, NULL);
        Window_StatusBar_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->Window_StatusBar_digital_clock_1, 55, 0);
    lv_obj_set_size(ui->Window_StatusBar_digital_clock_1, 134, 17);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_digital_clock_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_digital_clock_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Window_StatusBar_digital_clock_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Window_StatusBar_label_1
    ui->Window_StatusBar_label_1 = lv_label_create(ui->Window_StatusBar_cont_1);

    switch (My_UI.System_State_Of_Charge_Flag)
    {
    case My_UI.System_State_Of_Charge_ON_Battery_Free:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_EMPTY LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_1:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_1 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_2:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_2 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_3:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_3 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_1:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_1);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_2:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_2);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_3:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_3);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Full:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_FULL LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Full:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_FULL);
        break;

    default:
        break;
    }

    lv_label_set_long_mode(ui->Window_StatusBar_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Window_StatusBar_label_1, 190, 5);
    lv_obj_set_size(ui->Window_StatusBar_label_1, 50, 10);
    lv_obj_set_scrollbar_mode(ui->Window_StatusBar_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Window_StatusBar_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Window_StatusBar_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Window_StatusBar_label_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Window_StatusBar_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Window_StatusBar_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Window_StatusBar_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

/**
 * Create a demo application
 */
void custom_init(lv_ui *ui)
{
}
