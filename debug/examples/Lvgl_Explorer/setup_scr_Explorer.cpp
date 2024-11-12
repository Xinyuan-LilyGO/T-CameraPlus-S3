/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-10-05 11:27:57
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-06 14:02:17
 * @License: GPL 3.0
 */
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

void setup_scr_Explorer(lv_ui *ui)
{
    String current_directory_merge;

    // 合并所有目录容器
    for (int i = 0; i < My_UI.AE_Current_Directory.size(); i++)
    {
        if (My_UI.AE_Current_Directory[i] == "/") // 判断尾部是否有文件页操作符号
        {
            current_directory_merge = My_UI.AE_Current_Directory[i];
        }
        else
        {
            current_directory_merge = current_directory_merge + "/" + My_UI.AE_Current_Directory[i];
        }
    }

    My_UI.Explorer_list_1_folder.clear();
    My_UI.Explorer_list_1_file.clear();
    My_UI.AE_Folder_Name.clear();
    My_UI.AE_File_Manager_S.clear();

    if (SD_Initialization() != true)
    {
        My_UI.AE_SD_Mode_Flag = false;
        My_UI.AE_Current_Directory.clear();
        current_directory_merge = "/";
        My_UI.AE_Current_Directory.push_back("/");

        // Write codes Explorer
        ui->Explorer = lv_obj_create(NULL);
        lv_obj_set_size(ui->Explorer, 240, 240);
        lv_obj_set_scrollbar_mode(ui->Explorer, LV_SCROLLBAR_MODE_OFF);

        // Write style for Explorer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
        lv_obj_set_style_bg_opa(ui->Explorer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui->Explorer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write codes Explorer_list_1
        ui->Explorer_list_1 = lv_list_create(ui->Explorer);
        ui->Explorer_list_1_item0 = lv_list_add_btn(ui->Explorer_list_1, LV_SYMBOL_SD_CARD,
                                                    (".." + current_directory_merge).c_str());
        lv_obj_set_pos(ui->Explorer_list_1, 0, 0);
        lv_obj_set_size(ui->Explorer_list_1, 240, 240);
        lv_obj_set_scrollbar_mode(ui->Explorer_list_1, LV_SCROLLBAR_MODE_OFF);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_main_main_default
        static lv_style_t style_Explorer_list_1_main_main_default;
        ui_init_style(&style_Explorer_list_1_main_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_main_main_default, 20);
        lv_style_set_pad_left(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_pad_right(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_bg_opa(&style_Explorer_list_1_main_main_default, 255);
        lv_style_set_bg_color(&style_Explorer_list_1_main_main_default, lv_color_hex(0x000000));
        lv_style_set_border_width(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_radius(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_shadow_width(&style_Explorer_list_1_main_main_default, 0);
        lv_obj_add_style(ui->Explorer_list_1, &style_Explorer_list_1_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_main_scrollbar_default
        static lv_style_t style_Explorer_list_1_main_scrollbar_default;
        ui_init_style(&style_Explorer_list_1_main_scrollbar_default);

        lv_style_set_radius(&style_Explorer_list_1_main_scrollbar_default, 3);
        lv_style_set_bg_opa(&style_Explorer_list_1_main_scrollbar_default, 255);
        lv_style_set_bg_color(&style_Explorer_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
        lv_obj_add_style(ui->Explorer_list_1, &style_Explorer_list_1_main_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_extra_btns_main_default
        static lv_style_t style_Explorer_list_1_extra_btns_main_default;
        ui_init_style(&style_Explorer_list_1_extra_btns_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_extra_btns_main_default, 5);
        lv_style_set_pad_left(&style_Explorer_list_1_extra_btns_main_default, 10);
        lv_style_set_pad_right(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_extra_btns_main_default, 10);
        lv_style_set_border_width(&style_Explorer_list_1_extra_btns_main_default, 1);
        lv_style_set_border_opa(&style_Explorer_list_1_extra_btns_main_default, 255);
        lv_style_set_border_color(&style_Explorer_list_1_extra_btns_main_default, lv_color_hex(0x6f6969));
        lv_style_set_text_color(&style_Explorer_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
        lv_style_set_text_font(&style_Explorer_list_1_extra_btns_main_default, &lv_font_FontAwesome5_18);
        lv_style_set_radius(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_style_set_bg_opa(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_obj_add_style(ui->Explorer_list_1_item0, &style_Explorer_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_extra_texts_main_default
        static lv_style_t style_Explorer_list_1_extra_texts_main_default;
        ui_init_style(&style_Explorer_list_1_extra_texts_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_extra_texts_main_default, 6);
        lv_style_set_pad_left(&style_Explorer_list_1_extra_texts_main_default, 5);
        lv_style_set_pad_right(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_border_width(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_text_color(&style_Explorer_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
        lv_style_set_text_font(&style_Explorer_list_1_extra_texts_main_default, &lv_font_montserratMedium_18);
        lv_style_set_radius(&style_Explorer_list_1_extra_texts_main_default, 3);
        lv_style_set_bg_opa(&style_Explorer_list_1_extra_texts_main_default, 0);

        // Write codes Explorer_imgbtn_1
        ui->Explorer_imgbtn_1 = lv_imgbtn_create(ui->Explorer);
        lv_obj_add_flag(ui->Explorer_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
        lv_imgbtn_set_src(ui->Explorer_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_28_alpha_168x168, NULL);
        lv_imgbtn_set_src(ui->Explorer_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_27_alpha_168x168, NULL);
        lv_obj_add_flag(ui->Explorer_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
        ui->Explorer_imgbtn_1_label = lv_label_create(ui->Explorer_imgbtn_1);
        lv_label_set_text(ui->Explorer_imgbtn_1_label, "");
        lv_label_set_long_mode(ui->Explorer_imgbtn_1_label, LV_LABEL_LONG_WRAP);
        lv_obj_align(ui->Explorer_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_pad_all(ui->Explorer_imgbtn_1, 0, LV_STATE_DEFAULT);
        lv_obj_set_pos(ui->Explorer_imgbtn_1, 36, 59);
        lv_obj_set_size(ui->Explorer_imgbtn_1, 168, 168);
        lv_obj_set_scrollbar_mode(ui->Explorer_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

        // Write style for Explorer_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
        lv_obj_set_style_img_opa(ui->Explorer_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui->Explorer_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui->Explorer_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_align(ui->Explorer_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui->Explorer_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style for Explorer_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
        lv_obj_set_style_img_opa(ui->Explorer_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(ui->Explorer_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_font(ui->Explorer_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_shadow_width(ui->Explorer_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);

        // Write style for Explorer_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
        lv_obj_set_style_img_opa(ui->Explorer_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(ui->Explorer_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_font(ui->Explorer_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_shadow_width(ui->Explorer_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);

        // Update current screen layout.
        lv_obj_update_layout(ui->Explorer);

        // Init events for screen.
        events_init_Explorer(ui);
    }
    else
    {
        My_UI.AE_SD_Mode_Flag = true;
        File_Root_Initialization();

        AE_Class.File_Directory_Refresh(&SD, My_UI.AE_Current_Directory, &My_UI.AE_Folder_Name,
                                        &My_UI.AE_File_Manager_S);
        AE_Class.File_Directory_Sort(Arduino_Explorer::File_Manager_Sort_Order, &My_UI.AE_Folder_Name,
                                     &My_UI.AE_File_Manager_S);

        // Write codes Explorer
        ui->Explorer = lv_obj_create(NULL);
        lv_obj_set_size(ui->Explorer, 240, 240);
        lv_obj_set_scrollbar_mode(ui->Explorer, LV_SCROLLBAR_MODE_OFF);

        // Write style for Explorer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
        lv_obj_set_style_bg_opa(ui->Explorer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(ui->Explorer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write codes Explorer_list_1
        ui->Explorer_list_1 = lv_list_create(ui->Explorer);
        ui->Explorer_list_1_item0 = lv_list_add_btn(ui->Explorer_list_1, LV_SYMBOL_SD_CARD,
                                                    (".." + current_directory_merge).c_str());

        for (int i = 0; i < My_UI.AE_Folder_Name.size(); i++)
        {
            My_UI.Explorer_list_1_folder.push_back(lv_list_add_btn(ui->Explorer_list_1, LV_SYMBOL_DIRECTORY,
                                                                   My_UI.AE_Folder_Name[i].c_str()));
        }

        for (int i = 0; i < My_UI.AE_File_Manager_S.size(); i++)
        {
            My_UI.Explorer_list_1_file.push_back(lv_list_add_btn(ui->Explorer_list_1, LV_SYMBOL_FILE,
                                                                 (My_UI.AE_File_Manager_S[i].file_name + " " + My_UI.AE_File_Manager_S[i].file_size + "Kb          ").c_str()));
        }

        lv_obj_set_pos(ui->Explorer_list_1, 0, 0);
        lv_obj_set_size(ui->Explorer_list_1, 240, 240);
        lv_obj_set_scrollbar_mode(ui->Explorer_list_1, LV_SCROLLBAR_MODE_OFF);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_main_main_default
        static lv_style_t style_Explorer_list_1_main_main_default;
        ui_init_style(&style_Explorer_list_1_main_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_main_main_default, 20);
        lv_style_set_pad_left(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_pad_right(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_bg_opa(&style_Explorer_list_1_main_main_default, 255);
        lv_style_set_bg_color(&style_Explorer_list_1_main_main_default, lv_color_hex(0x000000));
        lv_style_set_border_width(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_radius(&style_Explorer_list_1_main_main_default, 0);
        lv_style_set_shadow_width(&style_Explorer_list_1_main_main_default, 0);
        lv_obj_add_style(ui->Explorer_list_1, &style_Explorer_list_1_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_main_scrollbar_default
        static lv_style_t style_Explorer_list_1_main_scrollbar_default;
        ui_init_style(&style_Explorer_list_1_main_scrollbar_default);

        lv_style_set_radius(&style_Explorer_list_1_main_scrollbar_default, 3);
        lv_style_set_bg_opa(&style_Explorer_list_1_main_scrollbar_default, 255);
        lv_style_set_bg_color(&style_Explorer_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
        lv_obj_add_style(ui->Explorer_list_1, &style_Explorer_list_1_main_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_extra_btns_main_default
        static lv_style_t style_Explorer_list_1_extra_btns_main_default;
        ui_init_style(&style_Explorer_list_1_extra_btns_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_extra_btns_main_default, 5);
        lv_style_set_pad_left(&style_Explorer_list_1_extra_btns_main_default, 10);
        lv_style_set_pad_right(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_extra_btns_main_default, 10);
        lv_style_set_border_width(&style_Explorer_list_1_extra_btns_main_default, 1);
        lv_style_set_border_opa(&style_Explorer_list_1_extra_btns_main_default, 255);
        lv_style_set_border_color(&style_Explorer_list_1_extra_btns_main_default, lv_color_hex(0x6f6969));
        lv_style_set_text_color(&style_Explorer_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
        lv_style_set_text_font(&style_Explorer_list_1_extra_btns_main_default, &lv_font_FontAwesome5_18);
        lv_style_set_radius(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_style_set_bg_opa(&style_Explorer_list_1_extra_btns_main_default, 0);
        lv_obj_add_style(ui->Explorer_list_1_item0, &style_Explorer_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
        for (int i = 0; i < My_UI.AE_Folder_Name.size(); i++)
        {
            lv_obj_add_style(My_UI.Explorer_list_1_folder[i], &style_Explorer_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        for (int i = 0; i < My_UI.AE_File_Manager_S.size(); i++)
        {
            lv_obj_add_style(My_UI.Explorer_list_1_file[i], &style_Explorer_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
        }

        // Write style state: LV_STATE_DEFAULT for &style_Explorer_list_1_extra_texts_main_default
        static lv_style_t style_Explorer_list_1_extra_texts_main_default;
        ui_init_style(&style_Explorer_list_1_extra_texts_main_default);

        lv_style_set_pad_top(&style_Explorer_list_1_extra_texts_main_default, 6);
        lv_style_set_pad_left(&style_Explorer_list_1_extra_texts_main_default, 5);
        lv_style_set_pad_right(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_pad_bottom(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_border_width(&style_Explorer_list_1_extra_texts_main_default, 0);
        lv_style_set_text_color(&style_Explorer_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
        lv_style_set_text_font(&style_Explorer_list_1_extra_texts_main_default, &lv_font_montserratMedium_18);
        lv_style_set_radius(&style_Explorer_list_1_extra_texts_main_default, 3);
        lv_style_set_bg_opa(&style_Explorer_list_1_extra_texts_main_default, 0);

        // Update current screen layout.
        lv_obj_update_layout(ui->Explorer);

        // Init events for screen.
        events_init_Explorer(ui);
    }
}
