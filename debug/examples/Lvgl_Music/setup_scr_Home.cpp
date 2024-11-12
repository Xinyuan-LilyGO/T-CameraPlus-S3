/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

int Home_digital_clock_1_min_value = 00;
int Home_digital_clock_1_hour_value = 00;
int Home_digital_clock_1_sec_value = 00;

void setup_scr_Home(lv_ui *ui)
{
    // Write codes Home
    ui->Home = lv_obj_create(NULL);
    lv_obj_set_size(ui->Home, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Home, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_carousel_1
    ui->Home_carousel_1 = lv_carousel_create(ui->Home);
    lv_carousel_set_element_width(ui->Home_carousel_1, 170);
    lv_obj_set_size(ui->Home_carousel_1, 240, 240);
    ui->Home_carousel_1_element_1 = lv_carousel_add_element(ui->Home_carousel_1, 0);
    ui->Home_carousel_1_element_2 = lv_carousel_add_element(ui->Home_carousel_1, 1);
    ui->Home_carousel_1_element_3 = lv_carousel_add_element(ui->Home_carousel_1, 2);
    ui->Home_carousel_1_element_4 = lv_carousel_add_element(ui->Home_carousel_1, 3);
    ui->Home_carousel_1_element_5 = lv_carousel_add_element(ui->Home_carousel_1, 4);
    ui->Home_carousel_1_element_6 = lv_carousel_add_element(ui->Home_carousel_1, 5);
    lv_obj_set_pos(ui->Home_carousel_1, 0, 0);
    lv_obj_set_size(ui->Home_carousel_1, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Home_carousel_1, LV_SCROLLBAR_MODE_ACTIVE);

    // Write style for Home_carousel_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_carousel_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_carousel_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_carousel_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_carousel_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Home_carousel_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_carousel_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_carousel_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Home_carousel_1_extra_element_items_default
    static lv_style_t style_Home_carousel_1_extra_element_items_default;
    ui_init_style(&style_Home_carousel_1_extra_element_items_default);

    lv_style_set_bg_opa(&style_Home_carousel_1_extra_element_items_default, 0);
    lv_style_set_outline_width(&style_Home_carousel_1_extra_element_items_default, 0);
    lv_style_set_border_width(&style_Home_carousel_1_extra_element_items_default, 0);
    lv_style_set_radius(&style_Home_carousel_1_extra_element_items_default, 5);
    lv_style_set_shadow_width(&style_Home_carousel_1_extra_element_items_default, 0);
    lv_obj_add_style(ui->Home_carousel_1_element_6, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->Home_carousel_1_element_5, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->Home_carousel_1_element_4, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->Home_carousel_1_element_3, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->Home_carousel_1_element_2, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui->Home_carousel_1_element_1, &style_Home_carousel_1_extra_element_items_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_FOCUSED for &style_Home_carousel_1_extra_element_items_focused
    static lv_style_t style_Home_carousel_1_extra_element_items_focused;
    ui_init_style(&style_Home_carousel_1_extra_element_items_focused);

    lv_style_set_bg_opa(&style_Home_carousel_1_extra_element_items_focused, 0);
    lv_style_set_outline_width(&style_Home_carousel_1_extra_element_items_focused, 0);
    lv_style_set_border_width(&style_Home_carousel_1_extra_element_items_focused, 0);
    lv_style_set_radius(&style_Home_carousel_1_extra_element_items_focused, 5);
    lv_style_set_shadow_width(&style_Home_carousel_1_extra_element_items_focused, 0);
    lv_obj_add_style(ui->Home_carousel_1_element_6, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(ui->Home_carousel_1_element_5, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(ui->Home_carousel_1_element_4, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(ui->Home_carousel_1_element_3, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(ui->Home_carousel_1_element_2, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_add_style(ui->Home_carousel_1_element_1, &style_Home_carousel_1_extra_element_items_focused, LV_PART_MAIN | LV_STATE_FOCUSED);

    // Write codes Home_btn_1
    ui->Home_btn_1 = lv_btn_create(ui->Home_carousel_1_element_1);
    ui->Home_btn_1_label = lv_label_create(ui->Home_btn_1);
    lv_label_set_text(ui->Home_btn_1_label, "");
    lv_label_set_long_mode(ui->Home_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_1, 15, 40);
    lv_obj_set_size(ui->Home_btn_1, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_1, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_1, &_1_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_1, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_1
    ui->Home_label_1 = lv_label_create(ui->Home_carousel_1_element_1);
    lv_label_set_text(ui->Home_label_1, "Playing");
    lv_label_set_long_mode(ui->Home_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_1, 37, 195);
    lv_obj_set_size(ui->Home_label_1, 98, 22);
    lv_obj_set_scrollbar_mode(ui->Home_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_1, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_btn_2
    ui->Home_btn_2 = lv_btn_create(ui->Home_carousel_1_element_2);
    ui->Home_btn_2_label = lv_label_create(ui->Home_btn_2);
    lv_label_set_text(ui->Home_btn_2_label, "");
    lv_label_set_long_mode(ui->Home_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_2, 15, 40);
    lv_obj_set_size(ui->Home_btn_2, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_2, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_2, &_2_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_2, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_2
    ui->Home_label_2 = lv_label_create(ui->Home_carousel_1_element_2);
    lv_label_set_text(ui->Home_label_2, "My Music");
    lv_label_set_long_mode(ui->Home_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_2, 33, 195);
    lv_obj_set_size(ui->Home_label_2, 105, 22);
    lv_obj_set_scrollbar_mode(ui->Home_label_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_2, &lv_font_FontAwesome5_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_btn_3
    ui->Home_btn_3 = lv_btn_create(ui->Home_carousel_1_element_3);
    ui->Home_btn_3_label = lv_label_create(ui->Home_btn_3);
    lv_label_set_text(ui->Home_btn_3_label, "");
    lv_label_set_long_mode(ui->Home_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_3, 15, 40);
    lv_obj_set_size(ui->Home_btn_3, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_3, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_3, &_15_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_3, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_3
    ui->Home_label_3 = lv_label_create(ui->Home_carousel_1_element_3);
    lv_label_set_text(ui->Home_label_3, "Settings");
    lv_label_set_long_mode(ui->Home_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_3, 37, 195);
    lv_obj_set_size(ui->Home_label_3, 98, 22);
    lv_obj_set_scrollbar_mode(ui->Home_label_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_3, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_btn_4
    ui->Home_btn_4 = lv_btn_create(ui->Home_carousel_1_element_4);
    ui->Home_btn_4_label = lv_label_create(ui->Home_btn_4);
    lv_label_set_text(ui->Home_btn_4_label, "");
    lv_label_set_long_mode(ui->Home_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_4, 15, 40);
    lv_obj_set_size(ui->Home_btn_4, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_4, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_4, &_24_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_4, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_4
    ui->Home_label_4 = lv_label_create(ui->Home_carousel_1_element_4);
    lv_label_set_text(ui->Home_label_4, "Camera");
    lv_label_set_long_mode(ui->Home_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_4, 37, 195);
    lv_obj_set_size(ui->Home_label_4, 98, 22);
    lv_obj_set_scrollbar_mode(ui->Home_label_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_4, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_btn_5
    ui->Home_btn_5 = lv_btn_create(ui->Home_carousel_1_element_5);
    ui->Home_btn_5_label = lv_label_create(ui->Home_btn_5);
    lv_label_set_text(ui->Home_btn_5_label, "");
    lv_label_set_long_mode(ui->Home_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_5, 15, 40);
    lv_obj_set_size(ui->Home_btn_5, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_5, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_5, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_5, &_25_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_5, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_5
    ui->Home_label_5 = lv_label_create(ui->Home_carousel_1_element_5);
    lv_label_set_text(ui->Home_label_5, "Recorder");
    lv_label_set_long_mode(ui->Home_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_5, 18, 195);
    lv_obj_set_size(ui->Home_label_5, 140, 20);
    lv_obj_set_scrollbar_mode(ui->Home_label_5, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_5, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_5, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_btn_6
    ui->Home_btn_6 = lv_btn_create(ui->Home_carousel_1_element_6);
    ui->Home_btn_6_label = lv_label_create(ui->Home_btn_6);
    lv_label_set_text(ui->Home_btn_6_label, "");
    lv_label_set_long_mode(ui->Home_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Home_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Home_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Home_btn_6, 15, 40);
    lv_obj_set_size(ui->Home_btn_6, 140, 140);
    lv_obj_set_scrollbar_mode(ui->Home_btn_6, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Home_btn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Home_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_btn_6, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_btn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->Home_btn_6, &_26_140x140, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->Home_btn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_btn_6, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_6
    ui->Home_label_6 = lv_label_create(ui->Home_carousel_1_element_6);
    lv_label_set_text(ui->Home_label_6, "Explorer");
    lv_label_set_long_mode(ui->Home_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_6, 15, 195);
    lv_obj_set_size(ui->Home_label_6, 140, 20);
    lv_obj_set_scrollbar_mode(ui->Home_label_6, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_6, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_6, &lv_font_arial_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_cont_1
    ui->Home_cont_1 = lv_obj_create(ui->Home);
    lv_obj_set_pos(ui->Home_cont_1, 0, 0);
    lv_obj_set_size(ui->Home_cont_1, 240, 21);
    lv_obj_set_scrollbar_mode(ui->Home_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Home_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_digital_clock_1
    static bool Home_digital_clock_1_timer_enabled = false;
    ui->Home_digital_clock_1 = lv_dclock_create(ui->Home_cont_1, "00:00:00");
    if (!Home_digital_clock_1_timer_enabled)
    {
        lv_timer_create(Home_digital_clock_1_timer, 1000, NULL);
        Home_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->Home_digital_clock_1, 55, 0);
    lv_obj_set_size(ui->Home_digital_clock_1, 134, 17);
    lv_obj_set_scrollbar_mode(ui->Home_digital_clock_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_digital_clock_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_digital_clock_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Home_label_8
    ui->Home_label_8 = lv_label_create(ui->Home_cont_1);

    switch (My_UI.System_State_Of_Charge_Flag)
    {
    case My_UI.System_State_Of_Charge_ON_Battery_Free:
        lv_label_set_text(ui->Home_label_8, LV_SYMBOL_BATTERY_EMPTY LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_1:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_2:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_3:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_1:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_2:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_3:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Full:
        /* code */
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Full:
        /* code */
        break;

    default:
        break;
    }

    lv_label_set_long_mode(ui->Home_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Home_label_8, 175, 5);
    lv_obj_set_size(ui->Home_label_8, 100, 30);
    lv_obj_set_scrollbar_mode(ui->Home_label_8, LV_SCROLLBAR_MODE_OFF);

    // Write style for Home_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Home_label_8, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Home_label_8, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Home_label_8, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Home_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Home_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Update current screen layout.
    lv_obj_update_layout(ui->Home);

    // Init events for screen.
    events_init_Home(ui);
}
