/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-11-13 17:50:10
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2024-01-24 17:27:15
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Camera(lv_ui *ui)
{
    // Write codes Camera
    ui->Camera = lv_obj_create(NULL);
    lv_obj_set_size(ui->Camera, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Camera, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Camera, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Camera_btnm_1
    ui->Camera_btnm_1 = lv_btnmatrix_create(ui->Camera);
    static const char *Camera_btnm_1_text_map[] = {
        "Wifi STA",
        "\n",
        "Wifi SoftAP",
        // "\n",
        // "Screen",
        "",
    };
    lv_btnmatrix_set_map(ui->Camera_btnm_1, Camera_btnm_1_text_map);
    lv_obj_set_pos(ui->Camera_btnm_1, 42, 60);
    lv_obj_set_size(ui->Camera_btnm_1, 156, 172);
    lv_obj_set_scrollbar_mode(ui->Camera_btnm_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Camera_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Camera_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Camera_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Camera_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Camera_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->Camera_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->Camera_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Camera_btnm_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Camera_btnm_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_btnm_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Camera_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Camera_btnm_1, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Camera_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Camera_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Camera_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Camera_btnm_1, &lv_font_montserratMedium_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Camera_btnm_1, 4, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Camera_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_btnm_1, lv_color_hex(0x2195f6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Camera_btnm_1, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write codes Camera_label_1
    ui->Camera_label_1 = lv_label_create(ui->Camera);
    lv_label_set_text(ui->Camera_label_1, "Camera \nConnection Mode");
    lv_label_set_long_mode(ui->Camera_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Camera_label_1, 11, 20);
    lv_obj_set_size(ui->Camera_label_1, 218, 35);
    lv_obj_set_scrollbar_mode(ui->Camera_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Camera_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Camera_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Camera_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Camera_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Camera_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Camera);

    // Update current screen layout.
    lv_obj_update_layout(ui->Camera);

    // Init events for screen.
    events_init_Camera(ui);
}
