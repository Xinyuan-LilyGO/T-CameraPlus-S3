/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-06 10:54:55
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 16:17:34
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"

void ui_init_style(lv_style_t *style)
{
    if (style->prop_cnt > 1)
        lv_style_reset(style);
    else
        lv_style_init(style);
}

void init_scr_del_flag(lv_ui *ui)
{
    ui->Home_del = true;
    ui->Playing_del = true;
    ui->My_Music_del = true;
    ui->Settings_del = true;
    ui->Camera_Wifi_del = true;
    ui->Recorder_del = true;
    ui->Explorer_del = true;
    ui->Music_list_del = true;
    ui->Music_file_scanning_del = true;
    ui->Battery_del = true;
    ui->WIFI_del = true;
    ui->Camera_del = true;
    ui->Camera_Screen_del = true;
}

void setup_ui(lv_ui *ui)
{
    init_scr_del_flag(ui);
    setup_scr_Home(ui);
    lv_scr_load(ui->Home);
}
