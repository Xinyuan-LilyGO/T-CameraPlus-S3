/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 11:22:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-20 10:32:41
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_My_Music(lv_ui *ui)
{
    // Write codes My_Music
    ui->My_Music = lv_obj_create(NULL);
    lv_obj_set_size(ui->My_Music, 240, 240);
    lv_obj_set_scrollbar_mode(ui->My_Music, LV_SCROLLBAR_MODE_OFF);

    // Write style for My_Music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->My_Music, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->My_Music, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes My_Music_list_1
    ui->My_Music_list_1 = lv_list_create(ui->My_Music);
    ui->My_Music_list_1_item0 = lv_list_add_btn(ui->My_Music_list_1, LV_SYMBOL_LIST, "Music list");
    ui->My_Music_list_1_item1 = lv_list_add_btn(ui->My_Music_list_1, LV_SYMBOL_REFRESH, "Music file scanning");
    lv_obj_set_pos(ui->My_Music_list_1, 0, 0);
    lv_obj_set_size(ui->My_Music_list_1, 240, 240);
    lv_obj_set_scrollbar_mode(ui->My_Music_list_1, LV_SCROLLBAR_MODE_OFF);

    // Write style state: LV_STATE_DEFAULT for &style_My_Music_list_1_main_main_default
    static lv_style_t style_My_Music_list_1_main_main_default;
    ui_init_style(&style_My_Music_list_1_main_main_default);

    lv_style_set_pad_top(&style_My_Music_list_1_main_main_default, 20);
    lv_style_set_pad_left(&style_My_Music_list_1_main_main_default, 0);
    lv_style_set_pad_right(&style_My_Music_list_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_My_Music_list_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_My_Music_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_My_Music_list_1_main_main_default, lv_color_hex(0x000000));
    lv_style_set_border_width(&style_My_Music_list_1_main_main_default, 0);
    lv_style_set_radius(&style_My_Music_list_1_main_main_default, 0);
    lv_style_set_shadow_width(&style_My_Music_list_1_main_main_default, 0);
    lv_obj_add_style(ui->My_Music_list_1, &style_My_Music_list_1_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_My_Music_list_1_main_scrollbar_default
    static lv_style_t style_My_Music_list_1_main_scrollbar_default;
    ui_init_style(&style_My_Music_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_My_Music_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_My_Music_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_My_Music_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_obj_add_style(ui->My_Music_list_1, &style_My_Music_list_1_main_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_My_Music_list_1_extra_btns_main_default
    static lv_style_t style_My_Music_list_1_extra_btns_main_default;
    ui_init_style(&style_My_Music_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_My_Music_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_My_Music_list_1_extra_btns_main_default, 10);
    lv_style_set_pad_right(&style_My_Music_list_1_extra_btns_main_default, 0);
    lv_style_set_pad_bottom(&style_My_Music_list_1_extra_btns_main_default, 10);
    lv_style_set_border_width(&style_My_Music_list_1_extra_btns_main_default, 1);
    lv_style_set_border_opa(&style_My_Music_list_1_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_My_Music_list_1_extra_btns_main_default, lv_color_hex(0x6f6969));
    lv_style_set_text_color(&style_My_Music_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
    lv_style_set_text_font(&style_My_Music_list_1_extra_btns_main_default, &lv_font_FontAwesome5_18);
    lv_style_set_radius(&style_My_Music_list_1_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_My_Music_list_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->My_Music_list_1_item1, &style_My_Music_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->My_Music_list_1_item0, &style_My_Music_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_My_Music_list_1_extra_texts_main_default
    static lv_style_t style_My_Music_list_1_extra_texts_main_default;
    ui_init_style(&style_My_Music_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_My_Music_list_1_extra_texts_main_default, 6);
    lv_style_set_pad_left(&style_My_Music_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_My_Music_list_1_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_My_Music_list_1_extra_texts_main_default, 0);
    lv_style_set_border_width(&style_My_Music_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_My_Music_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_My_Music_list_1_extra_texts_main_default, &lv_font_montserratMedium_18);
    lv_style_set_radius(&style_My_Music_list_1_extra_texts_main_default, 3);
    lv_style_set_bg_opa(&style_My_Music_list_1_extra_texts_main_default, 0);

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->My_Music);

    // Update current screen layout.
    lv_obj_update_layout(ui->My_Music);

    // Init events for screen.
    events_init_My_Music(ui);
}
