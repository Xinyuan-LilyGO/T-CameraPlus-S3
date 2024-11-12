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

void setup_scr_Playing(lv_ui *ui)
{
    // Write codes Playing
    ui->Playing = lv_obj_create(NULL);
    ui->Playing->user_data = (void *)"Playing"; // 记录当前窗口名

    lv_obj_set_size(ui->Playing, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Playing, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_imgbtn_1
    ui->Playing_imgbtn_1 = lv_imgbtn_create(ui->Playing);
    lv_obj_add_flag(ui->Playing_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_9_alpha_60x60, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_10_alpha_60x60, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_7_alpha_60x60, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_8_alpha_60x60, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_1_label = lv_label_create(ui->Playing_imgbtn_1);
    lv_label_set_text(ui->Playing_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_1, 90, 90);
    lv_obj_set_size(ui->Playing_imgbtn_1, 60, 60);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Playing)
    {
        lv_imgbtn_set_state(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED);
    }
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Pause)
    {
        lv_imgbtn_set_state(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_RELEASED);
    }
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Switch)
    {
        lv_imgbtn_set_state(ui->Playing_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED);
    }

    // Write codes Playing_imgbtn_2
    ui->Playing_imgbtn_2 = lv_imgbtn_create(ui->Playing);
    lv_obj_add_flag(ui->Playing_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_11_alpha_30x30, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_12_alpha_30x30, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_2_label = lv_label_create(ui->Playing_imgbtn_2);
    lv_label_set_text(ui->Playing_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_2, 185, 105);
    lv_obj_set_size(ui->Playing_imgbtn_2, 30, 30);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_2, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_2, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Playing_imgbtn_3
    ui->Playing_imgbtn_3 = lv_imgbtn_create(ui->Playing);
    lv_obj_add_flag(ui->Playing_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_3, LV_IMGBTN_STATE_RELEASED, NULL, &_13_alpha_30x30, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_3, LV_IMGBTN_STATE_PRESSED, NULL, &_14_alpha_30x30, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_3, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_3_label = lv_label_create(ui->Playing_imgbtn_3);
    lv_label_set_text(ui->Playing_imgbtn_3_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_3, 25, 105);
    lv_obj_set_size(ui->Playing_imgbtn_3, 30, 30);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_3, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_3, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_3, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_3, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Playing_label_1
    ui->Playing_label_1 = lv_label_create(ui->Playing);
    lv_label_set_text(ui->Playing_label_1, (My_UI.Playing_Current_Music_Name).c_str());
    lv_label_set_long_mode(ui->Playing_label_1, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->Playing_label_1, 13, 30);
    lv_obj_set_size(ui->Playing_label_1, 215, 30);
    lv_obj_set_scrollbar_mode(ui->Playing_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_label_1, &lv_font_simsun_16_cjk, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Playing_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_slider_3
    ui->Playing_slider_3 = lv_slider_create(ui->Playing);
    lv_slider_set_range(ui->Playing_slider_3, 0, My_UI.Playing_Current_Music_File_Duration + 1);
    lv_slider_set_value(ui->Playing_slider_3, My_UI.Playing_Current_Music_Time, lv_anim_enable_t::LV_ANIM_OFF);

    lv_obj_set_pos(ui->Playing_slider_3, 20, 210);
    lv_obj_set_size(ui->Playing_slider_3, 200, 8);
    lv_obj_set_scrollbar_mode(ui->Playing_slider_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_slider_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_3, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_3, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Playing_slider_3, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->Playing_slider_3, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_3, 44, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Playing_slider_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_slider_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_slider_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_3, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_3, lv_color_hex(0x5691f8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Playing_slider_3, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->Playing_slider_3, lv_color_hex(0xa666f1), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_3, 44, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for Playing_slider_3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_3, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_3, 44, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes Playing_label_2
    ui->Playing_label_2 = lv_label_create(ui->Playing);
    lv_label_set_text_fmt(ui->Playing_label_2, "%02d:%02d",
                          My_UI.Playing_Current_Music_Time / 60,
                          My_UI.Playing_Current_Music_Time % 60);

    lv_label_set_long_mode(ui->Playing_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Playing_label_2, 3, 190);
    lv_obj_set_size(ui->Playing_label_2, 74, 23);
    lv_obj_set_scrollbar_mode(ui->Playing_label_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_label_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_label_2, &lv_font_arial_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Playing_label_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_label_3
    ui->Playing_label_3 = lv_label_create(ui->Playing);
    lv_label_set_text_fmt(ui->Playing_label_3, "%02d:%02d",
                          My_UI.Playing_Current_Music_File_Duration / 60,
                          My_UI.Playing_Current_Music_File_Duration % 60);

    lv_label_set_long_mode(ui->Playing_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Playing_label_3, 163, 190);
    lv_obj_set_size(ui->Playing_label_3, 74, 23);
    lv_obj_set_scrollbar_mode(ui->Playing_label_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_label_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_label_3, &lv_font_arial_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Playing_label_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_label_4
    ui->Playing_label_4 = lv_label_create(ui->Playing);
    lv_label_set_text(ui->Playing_label_4,
                      ((String)(My_UI.Music_List_Current_Number + 1) + "/" + (String)(My_UI.Music_List_Total_Number)).c_str());
    lv_label_set_long_mode(ui->Playing_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Playing_label_4, 70, 185);
    lv_obj_set_size(ui->Playing_label_4, 100, 16);
    lv_obj_set_scrollbar_mode(ui->Playing_label_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_label_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_label_4, &lv_font_arial_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Playing_label_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_cont_2
    ui->Playing_cont_2 = lv_obj_create(ui->Playing);
    lv_obj_set_pos(ui->Playing_cont_2, 0, -2);
    lv_obj_set_size(ui->Playing_cont_2, 240, 180);
    lv_obj_set_scrollbar_mode(ui->Playing_cont_2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->Playing_cont_2, LV_OBJ_FLAG_HIDDEN);

    // Write style for Playing_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Playing_cont_2, 231, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_cont_2, lv_color_hex(0x2e2e2e), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_cont_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Playing_slider_1
    ui->Playing_slider_1 = lv_slider_create(ui->Playing_cont_2);
    lv_slider_set_range(ui->Playing_slider_1, 0, 21);
    lv_slider_set_value(ui->Playing_slider_1, My_UI.Playing_Music_Volume, lv_anim_enable_t::LV_ANIM_OFF);
    lv_obj_set_pos(ui->Playing_slider_1, 60, 140);
    lv_obj_set_size(ui->Playing_slider_1, 165, 10);
    lv_obj_set_scrollbar_mode(ui->Playing_slider_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_1, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_1, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Playing_slider_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_slider_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_1, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for Playing_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_1, 50, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes Playing_imgbtn_4
    ui->Playing_imgbtn_4 = lv_imgbtn_create(ui->Playing_cont_2);
    lv_obj_add_flag(ui->Playing_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_4, LV_IMGBTN_STATE_RELEASED, NULL, &_16_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_4, LV_IMGBTN_STATE_PRESSED, NULL, &_18_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_4, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_20_alpha_50x50, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_4, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_4_label = lv_label_create(ui->Playing_imgbtn_4);
    lv_label_set_text(ui->Playing_imgbtn_4_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_4, 20, 20);
    lv_obj_set_size(ui->Playing_imgbtn_4, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_4, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_4, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_4, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Playing_slider_2
    ui->Playing_slider_2 = lv_slider_create(ui->Playing_cont_2);
    lv_slider_set_range(ui->Playing_slider_2, 0, 255);
    lv_slider_set_value(ui->Playing_slider_2, My_UI.System_Screen_Brightness, lv_anim_enable_t::LV_ANIM_OFF);
    lv_obj_set_pos(ui->Playing_slider_2, 60, 95);
    lv_obj_set_size(ui->Playing_slider_2, 165, 10);
    lv_obj_set_scrollbar_mode(ui->Playing_slider_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_slider_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_2, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_2, lv_color_hex(0x2195f6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_2, 50, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->Playing_slider_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_slider_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_slider_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_2, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_2, 50, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Write style for Playing_slider_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Playing_slider_2, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Playing_slider_2, lv_color_hex(0x2195f6), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Playing_slider_2, 50, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes Playing_imgbtn_5
    ui->Playing_imgbtn_5 = lv_imgbtn_create(ui->Playing_cont_2);
    lv_obj_add_flag(ui->Playing_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_5, LV_IMGBTN_STATE_RELEASED, NULL, &_17_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_5, LV_IMGBTN_STATE_PRESSED, NULL, &_19_alpha_50x50, NULL);
    lv_imgbtn_set_src(ui->Playing_imgbtn_5, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_21_alpha_50x50, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_5, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_5_label = lv_label_create(ui->Playing_imgbtn_5);
    lv_label_set_text(ui->Playing_imgbtn_5_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_5, 100, 20);
    lv_obj_set_size(ui->Playing_imgbtn_5, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_5, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_5, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_5, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_5, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_5, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Playing_imgbtn_6
    ui->Playing_imgbtn_6 = lv_imgbtn_create(ui->Playing_cont_2);
    lv_obj_add_flag(ui->Playing_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_6, LV_IMGBTN_STATE_RELEASED, NULL, &_22_alpha_30x30, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_6, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_6_label = lv_label_create(ui->Playing_imgbtn_6);
    lv_label_set_text(ui->Playing_imgbtn_6_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_6, 17, 85);
    lv_obj_set_size(ui->Playing_imgbtn_6, 30, 30);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_6, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_6, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_6, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_6, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_6, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Write codes Playing_imgbtn_7
    ui->Playing_imgbtn_7 = lv_imgbtn_create(ui->Playing_cont_2);
    lv_obj_add_flag(ui->Playing_imgbtn_7, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->Playing_imgbtn_7, LV_IMGBTN_STATE_RELEASED, NULL, &_23_alpha_27x27, NULL);
    lv_obj_add_flag(ui->Playing_imgbtn_7, LV_OBJ_FLAG_CHECKABLE);
    ui->Playing_imgbtn_7_label = lv_label_create(ui->Playing_imgbtn_7);
    lv_label_set_text(ui->Playing_imgbtn_7_label, "");
    lv_label_set_long_mode(ui->Playing_imgbtn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Playing_imgbtn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Playing_imgbtn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->Playing_imgbtn_7, 19, 130);
    lv_obj_set_size(ui->Playing_imgbtn_7, 27, 27);
    lv_obj_set_scrollbar_mode(ui->Playing_imgbtn_7, LV_SCROLLBAR_MODE_OFF);

    // Write style for Playing_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Playing_imgbtn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Playing_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_PRESSED);

    // Write style for Playing_imgbtn_7, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_opa(ui->Playing_imgbtn_7, 255, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->Playing_imgbtn_7, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->Playing_imgbtn_7, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->Playing_imgbtn_7, 0, LV_PART_MAIN | LV_STATE_CHECKED);

    // Update current screen layout.
    lv_obj_update_layout(ui->Playing);

    // Init events for screen.
    events_init_Playing(ui);
}
