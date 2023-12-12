/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-19 13:44:33
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-20 16:08:14
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Recorder(lv_ui *ui)
{
    // Write codes Recorder
    ui->Recorder = lv_obj_create(NULL);
    lv_obj_set_size(ui->Recorder, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Recorder, LV_SCROLLBAR_MODE_OFF);

    // Write style for Recorder, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Recorder, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Recorder, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Recorder_win_1
    ui->Recorder_win_1 = lv_win_create(ui->Recorder, 30);
    lv_win_add_title(ui->Recorder_win_1, "Recorder message box");
    lv_obj_t *Recorder_win_1_label = lv_label_create(lv_win_get_content(ui->Recorder_win_1));
    lv_obj_set_scrollbar_mode(lv_win_get_content(ui->Recorder_win_1), LV_SCROLLBAR_MODE_OFF);
    lv_label_set_text(Recorder_win_1_label, (My_UI.MSM261_Recording_Text).c_str());
    lv_obj_set_pos(ui->Recorder_win_1, 0, 20);
    lv_obj_set_size(ui->Recorder_win_1, 239, 154);
    lv_obj_set_scrollbar_mode(ui->Recorder_win_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Recorder_win_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Recorder_win_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Recorder_win_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Recorder_win_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Recorder_win_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Recorder_win_1_extra_content_main_default
    static lv_style_t style_Recorder_win_1_extra_content_main_default;
    ui_init_style(&style_Recorder_win_1_extra_content_main_default);

    lv_style_set_bg_opa(&style_Recorder_win_1_extra_content_main_default, 255);
    lv_style_set_bg_color(&style_Recorder_win_1_extra_content_main_default, lv_color_hex(0xeeeef6));
    lv_style_set_text_color(&style_Recorder_win_1_extra_content_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Recorder_win_1_extra_content_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_letter_space(&style_Recorder_win_1_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_Recorder_win_1_extra_content_main_default, 2);
    lv_obj_add_style(lv_win_get_content(ui->Recorder_win_1), &style_Recorder_win_1_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Recorder_win_1_extra_header_main_default
    static lv_style_t style_Recorder_win_1_extra_header_main_default;
    ui_init_style(&style_Recorder_win_1_extra_header_main_default);

    lv_style_set_bg_opa(&style_Recorder_win_1_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_Recorder_win_1_extra_header_main_default, lv_color_hex(0xe6e6e6));
    lv_style_set_text_color(&style_Recorder_win_1_extra_header_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_Recorder_win_1_extra_header_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_letter_space(&style_Recorder_win_1_extra_header_main_default, 0);
    lv_style_set_text_line_space(&style_Recorder_win_1_extra_header_main_default, 2);
    lv_obj_add_style(lv_win_get_header(ui->Recorder_win_1), &style_Recorder_win_1_extra_header_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Recorder_win_1_extra_btns_main_default
    static lv_style_t style_Recorder_win_1_extra_btns_main_default;
    ui_init_style(&style_Recorder_win_1_extra_btns_main_default);

    lv_style_set_radius(&style_Recorder_win_1_extra_btns_main_default, 8);
    lv_style_set_bg_opa(&style_Recorder_win_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_Recorder_win_1_extra_btns_main_default, lv_color_hex(0x2195f6));

    // Write codes Recorder_btnm_1
    ui->Recorder_btnm_1 = lv_btnmatrix_create(ui->Recorder);
    static const char *Recorder_btnm_1_text_map[] = {
        "Clear",
        "Recording",
        "",
    };
    lv_btnmatrix_set_map(ui->Recorder_btnm_1, Recorder_btnm_1_text_map);
    lv_obj_set_pos(ui->Recorder_btnm_1, 9, 188);
    lv_obj_set_size(ui->Recorder_btnm_1, 222, 41);
    lv_obj_set_scrollbar_mode(ui->Recorder_btnm_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Recorder_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Recorder_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Recorder_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Recorder_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Recorder_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Recorder_btnm_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->Recorder_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->Recorder_btnm_1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Recorder_btnm_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Recorder_btnm_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Recorder_btnm_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Recorder_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Recorder_btnm_1, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Recorder_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Recorder_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Recorder_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Recorder_btnm_1, &lv_font_montserratMedium_16, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Recorder_btnm_1, 4, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Recorder_btnm_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Recorder_btnm_1, lv_color_hex(0x2195f6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Recorder_btnm_1, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Recorder);

    // Update current screen layout.
    lv_obj_update_layout(ui->Recorder);

    // Init events for screen.
    events_init_Recorder(ui);
}
