/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 17:35:46
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-20 10:31:43
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Battery(lv_ui *ui)
{
    // Write codes Battery
    ui->Battery = lv_obj_create(NULL);
    ui->g_kb_Battery = lv_keyboard_create(ui->Battery);
    lv_keyboard_set_mode(ui->g_kb_Battery, LV_KEYBOARD_MODE_NUMBER); // 设置为数字模式
    lv_obj_add_event_cb(ui->g_kb_Battery, kb_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_add_flag(ui->g_kb_Battery, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_font(ui->g_kb_Battery, &lv_font_simsun_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui->Battery, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Battery, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Battery_tabview_1
    ui->Battery_tabview_1 = lv_tabview_create(ui->Battery, LV_DIR_TOP, 40);
    lv_obj_set_pos(ui->Battery_tabview_1, 0, 20);
    lv_obj_set_size(ui->Battery_tabview_1, 240, 220);
    lv_obj_set_scrollbar_mode(ui->Battery_tabview_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_tabview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_tabview_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_tabview_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Battery_tabview_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_tabview_1, &lv_font_arial_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Battery_tabview_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Battery_tabview_1, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_tabview_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_tabview_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_tabview_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Battery_tabview_1_extra_btnm_main_default
    static lv_style_t style_Battery_tabview_1_extra_btnm_main_default;
    ui_init_style(&style_Battery_tabview_1_extra_btnm_main_default);

    lv_style_set_bg_opa(&style_Battery_tabview_1_extra_btnm_main_default, 255);
    lv_style_set_bg_color(&style_Battery_tabview_1_extra_btnm_main_default, lv_color_hex(0xffffff));
    lv_style_set_border_width(&style_Battery_tabview_1_extra_btnm_main_default, 0);
    lv_style_set_radius(&style_Battery_tabview_1_extra_btnm_main_default, 0);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Battery_tabview_1), &style_Battery_tabview_1_extra_btnm_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Battery_tabview_1_extra_btnm_items_default
    static lv_style_t style_Battery_tabview_1_extra_btnm_items_default;
    ui_init_style(&style_Battery_tabview_1_extra_btnm_items_default);

    lv_style_set_text_color(&style_Battery_tabview_1_extra_btnm_items_default, lv_color_hex(0x4d4d4d));
    lv_style_set_text_font(&style_Battery_tabview_1_extra_btnm_items_default, &lv_font_montserratMedium_12);
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Battery_tabview_1), &style_Battery_tabview_1_extra_btnm_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_CHECKED for &style_Battery_tabview_1_extra_btnm_items_checked
    static lv_style_t style_Battery_tabview_1_extra_btnm_items_checked;
    ui_init_style(&style_Battery_tabview_1_extra_btnm_items_checked);

    lv_style_set_text_color(&style_Battery_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_text_font(&style_Battery_tabview_1_extra_btnm_items_checked, &lv_font_montserratMedium_12);
    lv_style_set_border_width(&style_Battery_tabview_1_extra_btnm_items_checked, 4);
    lv_style_set_border_opa(&style_Battery_tabview_1_extra_btnm_items_checked, 255);
    lv_style_set_border_color(&style_Battery_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_style_set_border_side(&style_Battery_tabview_1_extra_btnm_items_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_Battery_tabview_1_extra_btnm_items_checked, 0);
    lv_style_set_bg_opa(&style_Battery_tabview_1_extra_btnm_items_checked, 60);
    lv_style_set_bg_color(&style_Battery_tabview_1_extra_btnm_items_checked, lv_color_hex(0x2195f6));
    lv_obj_add_style(lv_tabview_get_tab_btns(ui->Battery_tabview_1), &style_Battery_tabview_1_extra_btnm_items_checked, LV_PART_ITEMS | LV_STATE_CHECKED);

    // Write codes Information
    ui->Battery_tabview_1_tab_1 = lv_tabview_add_tab(ui->Battery_tabview_1, "Information");
    lv_obj_t *Battery_tabview_1_tab_1_label = lv_label_create(ui->Battery_tabview_1_tab_1);
    lv_label_set_text(Battery_tabview_1_tab_1_label, "");

    // Write codes Battery_table_1
    ui->Battery_table_1 = lv_table_create(ui->Battery_tabview_1_tab_1);
    lv_table_set_col_cnt(ui->Battery_table_1, 2);
    lv_table_set_row_cnt(ui->Battery_table_1, 10);
    lv_table_set_cell_value(ui->Battery_table_1, 0, 0, "Bus mode:");
    lv_table_set_cell_value(ui->Battery_table_1, 1, 0, "Charge mode:");
    lv_table_set_cell_value(ui->Battery_table_1, 2, 0, "Total supply voltage:");
    lv_table_set_cell_value(ui->Battery_table_1, 3, 0, "Battery voltage:");
    lv_table_set_cell_value(ui->Battery_table_1, 4, 0, "System voltage:");
    lv_table_set_cell_value(ui->Battery_table_1, 5, 0, "Charge Voltage Limit:");
    lv_table_set_cell_value(ui->Battery_table_1, 6, 0, "Fast Charge Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_1, 7, 0, "Precharge Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_1, 8, 0, "Termination Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_1, 9, 0, "OTG Mode:");
    lv_table_set_cell_value(ui->Battery_table_1, 0, 1, (My_UI.Battery_Information_Bus_Mode).c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 1, 1, (My_UI.Battery_Information_Charge_Mode).c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 2, 1, ((String)My_UI.Battery_Information_Total_Supply_Voltage + " mV").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 3, 1, ((String)My_UI.Battery_Information_Battery_Voltage + " mV").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 4, 1, ((String)My_UI.Battery_Information_System_Voltage + " mV").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 5, 1, ((String)My_UI.Battery_Information_Charge_Voltage_Limit + " mV").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 6, 1, ((String)My_UI.Battery_Information_Fast_Charge_Current_Limit + " mA").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 7, 1, ((String)My_UI.Battery_Information_Precharge_Charge_Current_Limit + " mA").c_str());
    lv_table_set_cell_value(ui->Battery_table_1, 8, 1, ((String)My_UI.Battery_Information_Termination_Charge_Current_Limit + " mA").c_str());

    if (My_UI.Battery_Control_OTG_Mode_Flag == My_UI.Battery_Control_OTG_ON)
    {
        lv_table_set_cell_value(ui->Battery_table_1, 9, 1, "ON");
    }
    else
    {
        lv_table_set_cell_value(ui->Battery_table_1, 9, 1, "OFF");
    }

    lv_obj_set_pos(ui->Battery_table_1, -20, -10);
    lv_obj_set_scrollbar_mode(ui->Battery_table_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_table_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_table_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_table_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_table_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_table_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_table_1, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_table_1, &lv_font_montserratMedium_12, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_table_1, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_table_1, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_table_1, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_table_1, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_table_1, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Battery_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_table_1, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write codes Control
    ui->Battery_tabview_1_tab_2 = lv_tabview_add_tab(ui->Battery_tabview_1, "Control");
    lv_obj_t *Battery_tabview_1_tab_2_label = lv_label_create(ui->Battery_tabview_1_tab_2);
    lv_label_set_text(Battery_tabview_1_tab_2_label, "");

    // Write codes Battery_table_2
    ui->Battery_table_2 = lv_table_create(ui->Battery_tabview_1_tab_2);
    lv_table_set_col_cnt(ui->Battery_table_2, 2);
    lv_table_set_row_cnt(ui->Battery_table_2, 5);
    lv_table_set_cell_value(ui->Battery_table_2, 0, 0, "Charge Voltage Limit:");
    lv_table_set_cell_value(ui->Battery_table_2, 1, 0, "Fast Charge Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_2, 2, 0, "Precharge Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_2, 3, 0, "Termination Current Limit:");
    lv_table_set_cell_value(ui->Battery_table_2, 4, 0, "OTG Mode:");
    lv_table_set_cell_value(ui->Battery_table_2, 0, 1, "            mV");
    lv_table_set_cell_value(ui->Battery_table_2, 1, 1, "            mA");
    lv_table_set_cell_value(ui->Battery_table_2, 2, 1, "            mA");
    lv_table_set_cell_value(ui->Battery_table_2, 3, 1, "            mA");
    lv_table_set_cell_value(ui->Battery_table_2, 4, 1, "");
    lv_obj_set_pos(ui->Battery_table_2, -20, -10);
    lv_obj_set_scrollbar_mode(ui->Battery_table_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_table_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_table_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_table_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_table_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_table_2, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_table_2, lv_color_hex(0x393c41), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_table_2, &lv_font_montserratMedium_12, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_table_2, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_table_2, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_table_2, 3, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_table_2, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_table_2, lv_color_hex(0xd5dee6), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Battery_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_table_2, 10, LV_PART_ITEMS | LV_STATE_DEFAULT);

    // Write codes Battery_ta_1
    ui->Battery_ta_1 = lv_textarea_create(ui->Battery_tabview_1_tab_2);
    lv_textarea_set_text(ui->Battery_ta_1, ((String)My_UI.Battery_Control_Charge_Voltage_Limit).c_str());
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->Battery_ta_1, ta_event_cb, LV_EVENT_ALL, ui->g_kb_Battery);
#endif
    lv_obj_set_pos(ui->Battery_ta_1, 130, 5);
    lv_obj_set_size(ui->Battery_ta_1, 55, 25);
    lv_obj_set_scrollbar_mode(ui->Battery_ta_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_ta_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_ta_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_ta_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Battery_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_ta_1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_ta_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_ta_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_ta_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_ta_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_ta_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_ta_1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_1, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_1, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes Battery_ta_2
    ui->Battery_ta_2 = lv_textarea_create(ui->Battery_tabview_1_tab_2);
    lv_textarea_set_text(ui->Battery_ta_2, ((String)My_UI.Battery_Control_Fast_Charge_Current_Limit).c_str());
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->Battery_ta_2, ta_event_cb, LV_EVENT_ALL, ui->g_kb_Battery);
#endif
    lv_obj_set_pos(ui->Battery_ta_2, 130, 65);
    lv_obj_set_size(ui->Battery_ta_2, 55, 25);
    lv_obj_set_scrollbar_mode(ui->Battery_ta_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_ta_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_ta_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_ta_2, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Battery_ta_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_ta_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_ta_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_ta_2, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_ta_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_ta_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_ta_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_ta_2, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_ta_2, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_2, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_2, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes Battery_ta_3
    ui->Battery_ta_3 = lv_textarea_create(ui->Battery_tabview_1_tab_2);
    lv_textarea_set_text(ui->Battery_ta_3, ((String)My_UI.Battery_Control_Precharge_Charge_Current_Limit).c_str());
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->Battery_ta_3, ta_event_cb, LV_EVENT_ALL, ui->g_kb_Battery);
#endif
    lv_obj_set_pos(ui->Battery_ta_3, 130, 125);
    lv_obj_set_size(ui->Battery_ta_3, 55, 25);
    lv_obj_set_scrollbar_mode(ui->Battery_ta_3, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_ta_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_ta_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_ta_3, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Battery_ta_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_ta_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_ta_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_3, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_ta_3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_ta_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_ta_3, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_ta_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_ta_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_ta_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_ta_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_ta_3, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_ta_3, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_3, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_3, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes Battery_ta_4
    ui->Battery_ta_4 = lv_textarea_create(ui->Battery_tabview_1_tab_2);
    lv_textarea_set_text(ui->Battery_ta_4, ((String)My_UI.Battery_Control_Termination_Charge_Current_Limit).c_str());
#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
    lv_obj_add_event_cb(ui->Battery_ta_4, ta_event_cb, LV_EVENT_ALL, ui->g_kb_Battery);
#endif
    lv_obj_set_pos(ui->Battery_ta_4, 130, 185);
    lv_obj_set_size(ui->Battery_ta_4, 55, 25);
    lv_obj_set_scrollbar_mode(ui->Battery_ta_4, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_ta_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->Battery_ta_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Battery_ta_4, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Battery_ta_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Battery_ta_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Battery_ta_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_4, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_ta_4, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Battery_ta_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Battery_ta_4, lv_color_hex(0xe6e6e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_ta_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Battery_ta_4, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Battery_ta_4, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Battery_ta_4, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_4, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_ta_4, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_ta_4, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_ta_4, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_ta_4, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write codes Battery_sw_1
    ui->Battery_sw_1 = lv_switch_create(ui->Battery_tabview_1_tab_2);
    lv_obj_set_pos(ui->Battery_sw_1, 155, 235);
    lv_obj_set_size(ui->Battery_sw_1, 40, 20);
    lv_obj_set_scrollbar_mode(ui->Battery_sw_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for Battery_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_sw_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_sw_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_sw_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Battery_sw_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for Battery_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->Battery_sw_1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->Battery_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->Battery_sw_1, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for Battery_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Battery_sw_1, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Battery_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Battery_sw_1, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Battery_sw_1, 100, LV_PART_KNOB | LV_STATE_DEFAULT);

    if (My_UI.Battery_Control_OTG_Mode_Flag ==My_UI.Battery_Control_OTG_ON)
    {
        lv_obj_add_state(ui->Battery_sw_1, LV_STATE_CHECKED); // 开
    }

    if (My_UI.Battery_Control_OTG_Mode_Flag == My_UI.Battery_Control_OTG_OFF)
    {
        lv_obj_clear_state(ui->Battery_sw_1, LV_STATE_CHECKED); // 关
    }

    if (My_UI.SY6970_Initialization_Flag == false)
    {
        // Write codes Battery_msgbox_1
        static const char *Battery_msgbox_1_btns[] = {"Close", "Retry", ""};
        ui->Battery_msgbox_1 = lv_msgbox_create(ui->Battery, "SY6970 Initialization Fail", "SY6970 equipment not found\nPlease refresh and try again\n", Battery_msgbox_1_btns, false);
        lv_obj_set_size(lv_msgbox_get_btns(ui->Battery_msgbox_1), 200, 30);
        lv_obj_set_pos(ui->Battery_msgbox_1, 5, 45);
        lv_obj_set_size(ui->Battery_msgbox_1, 230, 150);
        lv_obj_set_scrollbar_mode(ui->Battery_msgbox_1, LV_SCROLLBAR_MODE_OFF);

        // Write style for Battery_msgbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
        lv_obj_set_style_bg_opa(ui->Battery_msgbox_1, 231, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui->Battery_msgbox_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(ui->Battery_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(ui->Battery_msgbox_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui->Battery_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Battery_msgbox_1_extra_title_main_default
        static lv_style_t style_Battery_msgbox_1_extra_title_main_default;
        ui_init_style(&style_Battery_msgbox_1_extra_title_main_default);

        lv_style_set_text_color(&style_Battery_msgbox_1_extra_title_main_default, lv_color_hex(0xffffff));
        lv_style_set_text_font(&style_Battery_msgbox_1_extra_title_main_default, &lv_font_montserratMedium_12);
        lv_style_set_text_letter_space(&style_Battery_msgbox_1_extra_title_main_default, 0);
        lv_style_set_text_line_space(&style_Battery_msgbox_1_extra_title_main_default, 30);
        lv_obj_add_style(lv_msgbox_get_title(ui->Battery_msgbox_1), &style_Battery_msgbox_1_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Battery_msgbox_1_extra_content_main_default
        static lv_style_t style_Battery_msgbox_1_extra_content_main_default;
        ui_init_style(&style_Battery_msgbox_1_extra_content_main_default);

        lv_style_set_text_color(&style_Battery_msgbox_1_extra_content_main_default, lv_color_hex(0xffffff));
        lv_style_set_text_font(&style_Battery_msgbox_1_extra_content_main_default, &lv_font_montserratMedium_12);
        lv_style_set_text_letter_space(&style_Battery_msgbox_1_extra_content_main_default, 0);
        lv_style_set_text_line_space(&style_Battery_msgbox_1_extra_content_main_default, 10);
        lv_obj_add_style(lv_msgbox_get_text(ui->Battery_msgbox_1), &style_Battery_msgbox_1_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Battery_msgbox_1_extra_btns_items_default
        static lv_style_t style_Battery_msgbox_1_extra_btns_items_default;
        ui_init_style(&style_Battery_msgbox_1_extra_btns_items_default);

        lv_style_set_bg_opa(&style_Battery_msgbox_1_extra_btns_items_default, 255);
        lv_style_set_bg_color(&style_Battery_msgbox_1_extra_btns_items_default, lv_color_hex(0xe6e6e6));
        lv_style_set_border_width(&style_Battery_msgbox_1_extra_btns_items_default, 0);
        lv_style_set_radius(&style_Battery_msgbox_1_extra_btns_items_default, 10);
        lv_style_set_text_color(&style_Battery_msgbox_1_extra_btns_items_default, lv_color_hex(0x4e4e4e));
        lv_style_set_text_font(&style_Battery_msgbox_1_extra_btns_items_default, &lv_font_montserratMedium_12);
        lv_obj_add_style(lv_msgbox_get_btns(ui->Battery_msgbox_1), &style_Battery_msgbox_1_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);
    }

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Battery);

    // Update current screen layout.
    lv_obj_update_layout(ui->Battery);

    // Init events for screen.
    events_init_Battery(ui);
}
