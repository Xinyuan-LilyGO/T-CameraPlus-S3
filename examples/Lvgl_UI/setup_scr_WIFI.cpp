/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-17 17:27:16
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-20 10:33:22
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_WIFI(lv_ui *ui)
{
    My_UI.WIFI_LV_List_Name.clear(); // 每次都要清除

    // Write codes WIFI
    ui->WIFI = lv_obj_create(NULL);
    lv_obj_set_size(ui->WIFI, 240, 240);
    lv_obj_set_scrollbar_mode(ui->WIFI, LV_SCROLLBAR_MODE_OFF);

    // Write style for WIFI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WIFI, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WIFI, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes WIFI_list_1
    ui->WIFI_list_1 = lv_list_create(ui->WIFI);

    if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
    {
        for (int16_t i = 0; i < My_UI.WIFI_Manager_C.size(); i++)
        {
            My_UI.WIFI_LV_List_Name.push_back(lv_list_add_btn(ui->WIFI_list_1, LV_SYMBOL_WIFI,
                                                              (My_UI.WIFI_Manager_C[i].WIFI_Name + " (" +
                                                               My_UI.WIFI_Manager_C[i].WIFI_Signal + ")" +
                                                               ((My_UI.WIFI_Manager_C[i].WIFI_EncryptionType == 1) ? "*" : " "))
                                                                  .c_str()));
        }
    }

    lv_obj_set_pos(ui->WIFI_list_1, 0, 60);
    lv_obj_set_size(ui->WIFI_list_1, 240, 180);
    lv_obj_set_scrollbar_mode(ui->WIFI_list_1, LV_SCROLLBAR_MODE_OFF);

    // Write style state: LV_STATE_DEFAULT for &style_WIFI_list_1_main_main_default
    static lv_style_t style_WIFI_list_1_main_main_default;
    ui_init_style(&style_WIFI_list_1_main_main_default);

    lv_style_set_pad_top(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_pad_left(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_pad_right(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_WIFI_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_WIFI_list_1_main_main_default, lv_color_hex(0x000000));
    lv_style_set_border_width(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_radius(&style_WIFI_list_1_main_main_default, 0);
    lv_style_set_shadow_width(&style_WIFI_list_1_main_main_default, 0);
    lv_obj_add_style(ui->WIFI_list_1, &style_WIFI_list_1_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_WIFI_list_1_main_scrollbar_default
    static lv_style_t style_WIFI_list_1_main_scrollbar_default;
    ui_init_style(&style_WIFI_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_WIFI_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_WIFI_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_WIFI_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_obj_add_style(ui->WIFI_list_1, &style_WIFI_list_1_main_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_WIFI_list_1_extra_btns_main_default
    static lv_style_t style_WIFI_list_1_extra_btns_main_default;
    ui_init_style(&style_WIFI_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_WIFI_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_WIFI_list_1_extra_btns_main_default, 10);
    lv_style_set_pad_right(&style_WIFI_list_1_extra_btns_main_default, 0);
    lv_style_set_pad_bottom(&style_WIFI_list_1_extra_btns_main_default, 10);
    lv_style_set_border_width(&style_WIFI_list_1_extra_btns_main_default, 1);
    lv_style_set_border_opa(&style_WIFI_list_1_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_WIFI_list_1_extra_btns_main_default, lv_color_hex(0x6f6969));
    lv_style_set_text_color(&style_WIFI_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
    lv_style_set_text_font(&style_WIFI_list_1_extra_btns_main_default, &lv_font_simsun_16_cjk);
    lv_style_set_radius(&style_WIFI_list_1_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_WIFI_list_1_extra_btns_main_default, 0);

    if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
    {
        for (int16_t i = 0; i < My_UI.WIFI_Manager_C.size(); i++)
        {
            lv_obj_add_style(My_UI.WIFI_LV_List_Name[i], &style_WIFI_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    // Write style state: LV_STATE_DEFAULT for &style_WIFI_list_1_extra_texts_main_default
    static lv_style_t style_WIFI_list_1_extra_texts_main_default;
    ui_init_style(&style_WIFI_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_WIFI_list_1_extra_texts_main_default, 6);
    lv_style_set_pad_left(&style_WIFI_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_WIFI_list_1_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_WIFI_list_1_extra_texts_main_default, 0);
    lv_style_set_border_width(&style_WIFI_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_WIFI_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_WIFI_list_1_extra_texts_main_default, &lv_font_simsun_16_cjk);
    lv_style_set_radius(&style_WIFI_list_1_extra_texts_main_default, 3);
    lv_style_set_bg_opa(&style_WIFI_list_1_extra_texts_main_default, 0);

    // Write codes WIFI_sw_1
    ui->WIFI_sw_1 = lv_switch_create(ui->WIFI);
    lv_obj_set_pos(ui->WIFI_sw_1, 170, 30);
    lv_obj_set_size(ui->WIFI_sw_1, 40, 20);
    lv_obj_set_scrollbar_mode(ui->WIFI_sw_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for WIFI_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WIFI_sw_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WIFI_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WIFI_sw_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WIFI_sw_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WIFI_sw_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for WIFI_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->WIFI_sw_1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->WIFI_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->WIFI_sw_1, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for WIFI_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WIFI_sw_1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WIFI_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WIFI_sw_1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WIFI_sw_1, 100, LV_PART_KNOB | LV_STATE_DEFAULT);

    if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_ON)
    {
        lv_obj_add_state(ui->WIFI_sw_1, LV_STATE_CHECKED); // 开
    }

    if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_OFF)
    {
        lv_obj_clear_state(ui->WIFI_sw_1, LV_STATE_CHECKED); // 关
    }

    // Write codes WIFI_label_1
    ui->WIFI_label_1 = lv_label_create(ui->WIFI);
    lv_label_set_text(ui->WIFI_label_1, LV_SYMBOL_WIFI " WIFI");
    lv_label_set_long_mode(ui->WIFI_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WIFI_label_1, 0, 30);
    lv_obj_set_size(ui->WIFI_label_1, 130, 20);
    lv_obj_set_scrollbar_mode(ui->WIFI_label_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for WIFI_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WIFI_label_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WIFI_label_1, &lv_font_montserratMedium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WIFI_label_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WIFI_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WIFI_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
    {
        switch (My_UI.WIFI_Prompt_Flag)
        {
        case My_UI.WIFI_Prompt_Normal:

            break;
        case My_UI.WIFI_Prompt_Judgment_Encrypted:

            // Write codes WIFI_msgbox_1
            static const char *WIFI_msgbox_1_btns[] = {"NO", "YES", ""};
            ui->WIFI_msgbox_1 = lv_msgbox_create(ui->WIFI, "Connect WIFI",
                                                 ((My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name + " (" +
                                                   My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Signal + ")" +
                                                   ((My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_EncryptionType == 1) ? "*" : " ")) +
                                                  "\n\n")
                                                     .c_str(),
                                                 WIFI_msgbox_1_btns, false);

            lv_obj_set_size(lv_msgbox_get_btns(ui->WIFI_msgbox_1), 200, 30);
            lv_obj_set_pos(ui->WIFI_msgbox_1, 25, 40);
            lv_obj_set_size(ui->WIFI_msgbox_1, 190, 150);
            lv_obj_set_scrollbar_mode(ui->WIFI_msgbox_1, LV_SCROLLBAR_MODE_OFF);

            // Write style for WIFI_msgbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->WIFI_msgbox_1, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->WIFI_msgbox_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->WIFI_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->WIFI_msgbox_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->WIFI_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_1_extra_title_main_default
            static lv_style_t style_WIFI_msgbox_1_extra_title_main_default;
            ui_init_style(&style_WIFI_msgbox_1_extra_title_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_1_extra_title_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_1_extra_title_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_1_extra_title_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_1_extra_title_main_default, 30);
            lv_obj_add_style(lv_msgbox_get_title(ui->WIFI_msgbox_1), &style_WIFI_msgbox_1_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_1_extra_content_main_default
            static lv_style_t style_WIFI_msgbox_1_extra_content_main_default;
            ui_init_style(&style_WIFI_msgbox_1_extra_content_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_1_extra_content_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_1_extra_content_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_1_extra_content_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_1_extra_content_main_default, 10);
            lv_obj_add_style(lv_msgbox_get_text(ui->WIFI_msgbox_1), &style_WIFI_msgbox_1_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_1_extra_btns_items_default
            static lv_style_t style_WIFI_msgbox_1_extra_btns_items_default;
            ui_init_style(&style_WIFI_msgbox_1_extra_btns_items_default);

            lv_style_set_bg_opa(&style_WIFI_msgbox_1_extra_btns_items_default, 255);
            lv_style_set_bg_color(&style_WIFI_msgbox_1_extra_btns_items_default, lv_color_hex(0xe6e6e6));
            lv_style_set_border_width(&style_WIFI_msgbox_1_extra_btns_items_default, 0);
            lv_style_set_radius(&style_WIFI_msgbox_1_extra_btns_items_default, 10);
            lv_style_set_text_color(&style_WIFI_msgbox_1_extra_btns_items_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_1_extra_btns_items_default, &lv_font_montserratMedium_12);
            lv_obj_add_style(lv_msgbox_get_btns(ui->WIFI_msgbox_1), &style_WIFI_msgbox_1_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

            // Write codes g_kb_WIFI
            ui->g_kb_WIFI = lv_keyboard_create(ui->WIFI);
            lv_keyboard_set_mode(ui->g_kb_WIFI, LV_KEYBOARD_MODE_TEXT_LOWER); // 设置为字母小写模式
            lv_obj_add_event_cb(ui->g_kb_WIFI, kb_event_cb, LV_EVENT_ALL, NULL);
            lv_obj_add_flag(ui->g_kb_WIFI, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_text_font(ui->g_kb_WIFI, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write codes WIFI_ta_1
            ui->WIFI_ta_1 = lv_textarea_create(ui->WIFI);
            lv_textarea_set_text(ui->WIFI_ta_1, "");
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
            lv_obj_add_event_cb(ui->WIFI_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_WIFI);
#endif
            lv_obj_set_pos(ui->WIFI_ta_1, 40, 100);
            lv_obj_set_size(ui->WIFI_ta_1, 160, 30);
            lv_obj_set_scrollbar_mode(ui->WIFI_ta_1, LV_SCROLLBAR_MODE_OFF);

            // Write style for WIFI_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_text_color(ui->WIFI_ta_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(ui->WIFI_ta_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(ui->WIFI_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(ui->WIFI_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(ui->WIFI_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->WIFI_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->WIFI_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui->WIFI_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(ui->WIFI_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->WIFI_ta_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(ui->WIFI_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(ui->WIFI_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(ui->WIFI_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->WIFI_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style for WIFI_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->WIFI_ta_1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->WIFI_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->WIFI_ta_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

            break;
        case My_UI.WIFI_Prompt_Judgment_Unencrypted:
            /* code */
            break;

        case My_UI.WIFI_Prompt_Connect_Fail:

            // Write codes WIFI_msgbox_2
            static const char *WIFI_msgbox_2_btns[] = {"Close", ""};
            ui->WIFI_msgbox_2 = lv_msgbox_create(ui->WIFI, "Connect WIFI Fail",
                                                 ("WIFI:" + My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name + "\n\n").c_str(),
                                                 WIFI_msgbox_2_btns, false);

            lv_obj_set_size(lv_msgbox_get_btns(ui->WIFI_msgbox_2), 200, 30);
            lv_obj_set_pos(ui->WIFI_msgbox_2, 25, 40);
            lv_obj_set_size(ui->WIFI_msgbox_2, 190, 150);
            lv_obj_set_scrollbar_mode(ui->WIFI_msgbox_2, LV_SCROLLBAR_MODE_OFF);

            // Write style for WIFI_msgbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->WIFI_msgbox_2, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->WIFI_msgbox_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->WIFI_msgbox_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->WIFI_msgbox_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->WIFI_msgbox_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_2_extra_title_main_default
            static lv_style_t style_WIFI_msgbox_2_extra_title_main_default;
            ui_init_style(&style_WIFI_msgbox_2_extra_title_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_2_extra_title_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_2_extra_title_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_2_extra_title_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_2_extra_title_main_default, 30);
            lv_obj_add_style(lv_msgbox_get_title(ui->WIFI_msgbox_2), &style_WIFI_msgbox_2_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_2_extra_content_main_default
            static lv_style_t style_WIFI_msgbox_2_extra_content_main_default;
            ui_init_style(&style_WIFI_msgbox_2_extra_content_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_2_extra_content_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_2_extra_content_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_2_extra_content_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_2_extra_content_main_default, 10);
            lv_obj_add_style(lv_msgbox_get_text(ui->WIFI_msgbox_2), &style_WIFI_msgbox_2_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_2_extra_btns_items_default
            static lv_style_t style_WIFI_msgbox_2_extra_btns_items_default;
            ui_init_style(&style_WIFI_msgbox_2_extra_btns_items_default);

            lv_style_set_bg_opa(&style_WIFI_msgbox_2_extra_btns_items_default, 255);
            lv_style_set_bg_color(&style_WIFI_msgbox_2_extra_btns_items_default, lv_color_hex(0xe6e6e6));
            lv_style_set_border_width(&style_WIFI_msgbox_2_extra_btns_items_default, 0);
            lv_style_set_radius(&style_WIFI_msgbox_2_extra_btns_items_default, 10);
            lv_style_set_text_color(&style_WIFI_msgbox_2_extra_btns_items_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_2_extra_btns_items_default, &lv_font_montserratMedium_12);
            lv_obj_add_style(lv_msgbox_get_btns(ui->WIFI_msgbox_2), &style_WIFI_msgbox_2_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

            break;

        case My_UI.WIFI_Prompt_Connect_Successfully:

            // Write codes WIFI_msgbox_3
            static const char *WIFI_msgbox_3_btns[] = {"Close", ""};
            ui->WIFI_msgbox_3 = lv_msgbox_create(ui->WIFI, "Connect WIFI Successful",
                                                 ("WIFI Name: " + My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name + "\n\n").c_str(),
                                                 WIFI_msgbox_3_btns, false);

            lv_obj_set_size(lv_msgbox_get_btns(ui->WIFI_msgbox_3), 200, 30);
            lv_obj_set_pos(ui->WIFI_msgbox_3, 25, 40);
            lv_obj_set_size(ui->WIFI_msgbox_3, 190, 150);
            lv_obj_set_scrollbar_mode(ui->WIFI_msgbox_3, LV_SCROLLBAR_MODE_OFF);

            // Write style for WIFI_msgbox_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->WIFI_msgbox_3, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->WIFI_msgbox_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->WIFI_msgbox_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->WIFI_msgbox_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->WIFI_msgbox_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_3_extra_title_main_default
            static lv_style_t style_WIFI_msgbox_3_extra_title_main_default;
            ui_init_style(&style_WIFI_msgbox_3_extra_title_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_3_extra_title_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_3_extra_title_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_3_extra_title_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_3_extra_title_main_default, 30);
            lv_obj_add_style(lv_msgbox_get_title(ui->WIFI_msgbox_3), &style_WIFI_msgbox_3_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_3_extra_content_main_default
            static lv_style_t style_WIFI_msgbox_3_extra_content_main_default;
            ui_init_style(&style_WIFI_msgbox_3_extra_content_main_default);

            lv_style_set_text_color(&style_WIFI_msgbox_3_extra_content_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_3_extra_content_main_default, &lv_font_montserratMedium_12);
            lv_style_set_text_letter_space(&style_WIFI_msgbox_3_extra_content_main_default, 0);
            lv_style_set_text_line_space(&style_WIFI_msgbox_3_extra_content_main_default, 10);
            lv_obj_add_style(lv_msgbox_get_text(ui->WIFI_msgbox_3), &style_WIFI_msgbox_3_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_WIFI_msgbox_3_extra_btns_items_default
            static lv_style_t style_WIFI_msgbox_3_extra_btns_items_default;
            ui_init_style(&style_WIFI_msgbox_3_extra_btns_items_default);

            lv_style_set_bg_opa(&style_WIFI_msgbox_3_extra_btns_items_default, 255);
            lv_style_set_bg_color(&style_WIFI_msgbox_3_extra_btns_items_default, lv_color_hex(0xe6e6e6));
            lv_style_set_border_width(&style_WIFI_msgbox_3_extra_btns_items_default, 0);
            lv_style_set_radius(&style_WIFI_msgbox_3_extra_btns_items_default, 10);
            lv_style_set_text_color(&style_WIFI_msgbox_3_extra_btns_items_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_WIFI_msgbox_3_extra_btns_items_default, &lv_font_montserratMedium_12);
            lv_obj_add_style(lv_msgbox_get_btns(ui->WIFI_msgbox_3), &style_WIFI_msgbox_3_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

            break;

        default:
            break;
        }
    }

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->WIFI);

    // Update current screen layout.
    lv_obj_update_layout(ui->WIFI);

    // Init events for screen.
    events_init_WIFI(ui);
}
