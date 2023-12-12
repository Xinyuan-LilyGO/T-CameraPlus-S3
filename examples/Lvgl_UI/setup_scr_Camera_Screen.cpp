/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-11-21 11:08:09
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 14:56:39
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Camera_Screen(lv_ui *ui)
{
    // Write codes Camera_Screen
    ui->Camera_Screen = lv_obj_create(NULL);//需要创建窗口后才能记录当前窗口名
    ui->Camera_Screen->user_data = (void *)"Camera_Screen"; // 记录当前窗口名

    lv_obj_set_size(ui->Camera_Screen, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Camera_Screen, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera_Screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Camera_Screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_Screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Camera_Screen);

    // Update current screen layout.
    lv_obj_update_layout(ui->Camera_Screen);

    // Init events for screen.
    events_init_Camera_Screen(ui);
}
