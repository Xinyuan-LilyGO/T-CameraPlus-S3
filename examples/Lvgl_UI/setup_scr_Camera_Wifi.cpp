/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-18 17:16:39
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 16:17:17
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Camera_Wifi(lv_ui *ui)
{
    // Write codes Camera
    ui->Camera_Wifi = lv_obj_create(NULL);
    lv_obj_set_size(ui->Camera_Wifi, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Camera_Wifi, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Camera_Wifi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_Wifi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Camera_win_1
    ui->Camera_Wifi_win_1 = lv_win_create(ui->Camera_Wifi, 30);
    lv_win_add_title(ui->Camera_Wifi_win_1, "Camera message box");
    lv_obj_t *Camera_Wifi_win_1_label = lv_label_create(lv_win_get_content(ui->Camera_Wifi_win_1));
    lv_obj_set_scrollbar_mode(lv_win_get_content(ui->Camera_Wifi_win_1), LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(Camera_Wifi_win_1_label, "");
    lv_obj_set_pos(ui->Camera_Wifi_win_1, 0, 20);
    lv_obj_set_size(ui->Camera_Wifi_win_1, 239, 154);
    lv_obj_set_scrollbar_mode(ui->Camera_Wifi_win_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera_win_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Camera_Wifi_win_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_Wifi_win_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Camera_Wifi_win_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Camera_Wifi_win_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Camera_win_1_extra_content_main_default
    static lv_style_t style_Camera_Wifi_win_1_extra_content_main_default;
    ui_init_style(&style_Camera_Wifi_win_1_extra_content_main_default);

    lv_style_set_bg_opa(&style_Camera_Wifi_win_1_extra_content_main_default, 255);
    lv_style_set_bg_color(&style_Camera_Wifi_win_1_extra_content_main_default, lv_color_hex(0xeeeef6));
    lv_style_set_text_color(&style_Camera_Wifi_win_1_extra_content_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Camera_Wifi_win_1_extra_content_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_letter_space(&style_Camera_Wifi_win_1_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_Camera_Wifi_win_1_extra_content_main_default, 2);
    lv_obj_add_style(lv_win_get_content(ui->Camera_Wifi_win_1), &style_Camera_Wifi_win_1_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Camera_win_1_extra_header_main_default
    static lv_style_t style_Camera_Wifi_win_1_extra_header_main_default;
    ui_init_style(&style_Camera_Wifi_win_1_extra_header_main_default);

    lv_style_set_bg_opa(&style_Camera_Wifi_win_1_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_Camera_Wifi_win_1_extra_header_main_default, lv_color_hex(0xe6e6e6));
    lv_style_set_text_color(&style_Camera_Wifi_win_1_extra_header_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Camera_Wifi_win_1_extra_header_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_letter_space(&style_Camera_Wifi_win_1_extra_header_main_default, 0);
    lv_style_set_text_line_space(&style_Camera_Wifi_win_1_extra_header_main_default, 2);
    lv_obj_add_style(lv_win_get_header(ui->Camera_Wifi_win_1), &style_Camera_Wifi_win_1_extra_header_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Camera_win_1_extra_btns_main_default
    static lv_style_t style_Camera_Wifi_win_1_extra_btns_main_default;
    ui_init_style(&style_Camera_Wifi_win_1_extra_btns_main_default);

    lv_style_set_radius(&style_Camera_Wifi_win_1_extra_btns_main_default, 8);
    lv_style_set_bg_opa(&style_Camera_Wifi_win_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_Camera_Wifi_win_1_extra_btns_main_default, lv_color_hex(0x2195f6));

    // Write codes Camera_btnm_1
    ui->Camera_Wifi_btnm_1 = lv_btnmatrix_create(ui->Camera_Wifi);
    static const char *Camera_Wifi_btnm_1_text_map[] = {
        "Connect",
        "IR filter",
        "",
    };
    lv_btnmatrix_set_map(ui->Camera_Wifi_btnm_1, Camera_Wifi_btnm_1_text_map);
    lv_obj_set_pos(ui->Camera_Wifi_btnm_1, 9, 188);
    lv_obj_set_size(ui->Camera_Wifi_btnm_1, 222, 41);
    lv_obj_set_scrollbar_mode(ui->Camera_Wifi_btnm_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Camera_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Camera_Wifi_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Camera_Wifi_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Camera_Wifi_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Camera_Wifi_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Camera_Wifi_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->Camera_Wifi_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->Camera_Wifi_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Camera_Wifi_btnm_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Camera_Wifi_btnm_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_Wifi_btnm_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Camera_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Camera_Wifi_btnm_1, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Camera_Wifi_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Camera_Wifi_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Camera_Wifi_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Camera_Wifi_btnm_1, &lv_font_montserratMedium_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Camera_Wifi_btnm_1, 4, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Camera_Wifi_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Camera_Wifi_btnm_1, lv_color_hex(0x2195f6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Camera_Wifi_btnm_1, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Camera_Wifi);

    // Update current screen layout.
    lv_obj_update_layout(ui->Camera_Wifi);

    // Init events for screen.
    events_init_Camera_Wifi(ui);
}
