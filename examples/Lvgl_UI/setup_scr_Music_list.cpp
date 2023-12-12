/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 11:22:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-20 10:32:30
 * @License: GPL 3.0
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

void setup_scr_Music_list(lv_ui *ui)
{
    My_UI.AE_LV_List_File.clear();
    My_UI.AE_Folder_Name.clear();
    My_UI.AE_File_Manager_S.clear();

    // Write codes Music_list
    ui->Music_list = lv_obj_create(NULL);
    lv_obj_set_size(ui->Music_list, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Music_list, LV_SCROLLBAR_MODE_OFF);

    // Write style for Music_list, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Music_list, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes Music_list_list_1
    ui->Music_list_list_1 = lv_list_create(ui->Music_list);

    if (My_UI.Music_List_Total_Number != 0) // 如果有歌曲
    {
        ui->Music_list_list_1_item0 = lv_list_add_btn(ui->Music_list_list_1, LV_SYMBOL_DIRECTORY,
                                                      ("Music directory: " + My_UI.Music_List_Directory).c_str());

        for (int i = 0; i < My_UI.Music_List_File.size(); i++)
        {
            My_UI.AE_LV_List_File.push_back(lv_list_add_btn(ui->Music_list_list_1, LV_SYMBOL_AUDIO,
                                                            (My_UI.Music_List_File[i].file_name + " " + My_UI.Music_List_File[i].file_size + "Kb          ").c_str()));
        }
    }

    if (My_UI.Music_List_Total_Number == 0) // 如果没有歌曲
    {
        ui->Music_list_list_1_item0 = lv_list_add_btn(ui->Music_list_list_1, LV_SYMBOL_DIRECTORY,
                                                      "Music directory: NULL");
    }

    lv_obj_set_pos(ui->Music_list_list_1, 0, 0);
    lv_obj_set_size(ui->Music_list_list_1, 240, 240);
    lv_obj_set_scrollbar_mode(ui->Music_list_list_1, LV_SCROLLBAR_MODE_OFF);

    // Write style state: LV_STATE_DEFAULT for &style_Music_list_list_1_main_main_default
    static lv_style_t style_Music_list_list_1_main_main_default;
    ui_init_style(&style_Music_list_list_1_main_main_default);

    lv_style_set_pad_top(&style_Music_list_list_1_main_main_default, 20);
    lv_style_set_pad_left(&style_Music_list_list_1_main_main_default, 0);
    lv_style_set_pad_right(&style_Music_list_list_1_main_main_default, 0);
    lv_style_set_pad_bottom(&style_Music_list_list_1_main_main_default, 0);
    lv_style_set_bg_opa(&style_Music_list_list_1_main_main_default, 255);
    lv_style_set_bg_color(&style_Music_list_list_1_main_main_default, lv_color_hex(0x000000));
    lv_style_set_border_width(&style_Music_list_list_1_main_main_default, 0);
    lv_style_set_radius(&style_Music_list_list_1_main_main_default, 0);
    lv_style_set_shadow_width(&style_Music_list_list_1_main_main_default, 0);
    lv_obj_add_style(ui->Music_list_list_1, &style_Music_list_list_1_main_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Music_list_list_1_main_scrollbar_default
    static lv_style_t style_Music_list_list_1_main_scrollbar_default;
    ui_init_style(&style_Music_list_list_1_main_scrollbar_default);

    lv_style_set_radius(&style_Music_list_list_1_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_Music_list_list_1_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_Music_list_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_obj_add_style(ui->Music_list_list_1, &style_Music_list_list_1_main_scrollbar_default, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    // Write style state: LV_STATE_DEFAULT for &style_Music_list_list_1_extra_btns_main_default
    static lv_style_t style_Music_list_list_1_extra_btns_main_default;
    ui_init_style(&style_Music_list_list_1_extra_btns_main_default);

    lv_style_set_pad_top(&style_Music_list_list_1_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_Music_list_list_1_extra_btns_main_default, 10);
    lv_style_set_pad_right(&style_Music_list_list_1_extra_btns_main_default, 0);
    lv_style_set_pad_bottom(&style_Music_list_list_1_extra_btns_main_default, 10);
    lv_style_set_border_width(&style_Music_list_list_1_extra_btns_main_default, 1);
    lv_style_set_border_opa(&style_Music_list_list_1_extra_btns_main_default, 255);
    lv_style_set_border_color(&style_Music_list_list_1_extra_btns_main_default, lv_color_hex(0x6f6969));
    lv_style_set_text_color(&style_Music_list_list_1_extra_btns_main_default, lv_color_hex(0xfef6ea));
    lv_style_set_text_font(&style_Music_list_list_1_extra_btns_main_default, &lv_font_simsun_16_cjk);
    lv_style_set_radius(&style_Music_list_list_1_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_Music_list_list_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->Music_list_list_1_item0, &style_Music_list_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (My_UI.Music_List_Total_Number != 0) // 如果有歌曲
    {
        for (int i = 0; i < My_UI.Music_List_File.size(); i++)
        {
            lv_obj_add_style(My_UI.AE_LV_List_File[i], &style_Music_list_list_1_extra_btns_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }

    // Write style state: LV_STATE_DEFAULT for &style_Music_list_list_1_extra_texts_main_default
    static lv_style_t style_Music_list_list_1_extra_texts_main_default;
    ui_init_style(&style_Music_list_list_1_extra_texts_main_default);

    lv_style_set_pad_top(&style_Music_list_list_1_extra_texts_main_default, 6);
    lv_style_set_pad_left(&style_Music_list_list_1_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_Music_list_list_1_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_Music_list_list_1_extra_texts_main_default, 0);
    lv_style_set_border_width(&style_Music_list_list_1_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_Music_list_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_Music_list_list_1_extra_texts_main_default, &lv_font_simsun_16_cjk);
    lv_style_set_radius(&style_Music_list_list_1_extra_texts_main_default, 3);
    lv_style_set_bg_opa(&style_Music_list_list_1_extra_texts_main_default, 0);

    if (My_UI.Music_List_Total_Number != 0) // 如果有歌曲
    {
        switch (My_UI.Music_List_Prompt_Flag)
        {
        case My_UI.Music_List_Prompt_Normal:

            break;

        case My_UI.Music_List_Prompt_Play_Music_Judgment:

            // Write codes Music_list_msgbox_1
            static const char *Music_list_msgbox_1_btns[] = {"NO", "YES", ""};
            ui->Music_list_msgbox_1 = lv_msgbox_create(ui->Music_list, "Do you want to play music",
                                                       (My_UI.Music_List_File[My_UI.Music_List_Current_Number].file_name).c_str(), Music_list_msgbox_1_btns, false);
            lv_obj_set_size(lv_msgbox_get_btns(ui->Music_list_msgbox_1), 200, 30);
            lv_obj_set_pos(ui->Music_list_msgbox_1, 20, 30);
            lv_obj_set_size(ui->Music_list_msgbox_1, 200, 175);
            lv_obj_set_scrollbar_mode(ui->Music_list_msgbox_1, LV_SCROLLBAR_MODE_OFF);

            // Write style for Music_list_msgbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->Music_list_msgbox_1, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->Music_list_msgbox_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->Music_list_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->Music_list_msgbox_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->Music_list_msgbox_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_1_extra_title_main_default
            static lv_style_t style_Music_list_msgbox_1_extra_title_main_default;
            ui_init_style(&style_Music_list_msgbox_1_extra_title_main_default);

            lv_style_set_text_color(&style_Music_list_msgbox_1_extra_title_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_1_extra_title_main_default, &lv_font_simsun_16_cjk);
            lv_style_set_text_letter_space(&style_Music_list_msgbox_1_extra_title_main_default, 0);
            lv_style_set_text_line_space(&style_Music_list_msgbox_1_extra_title_main_default, 30);
            lv_obj_add_style(lv_msgbox_get_title(ui->Music_list_msgbox_1), &style_Music_list_msgbox_1_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_1_extra_content_main_default
            static lv_style_t style_Music_list_msgbox_1_extra_content_main_default;
            ui_init_style(&style_Music_list_msgbox_1_extra_content_main_default);

            lv_style_set_text_color(&style_Music_list_msgbox_1_extra_content_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_1_extra_content_main_default, &lv_font_simsun_16_cjk);
            lv_style_set_text_letter_space(&style_Music_list_msgbox_1_extra_content_main_default, 0);
            lv_style_set_text_line_space(&style_Music_list_msgbox_1_extra_content_main_default, 10);
            lv_obj_add_style(lv_msgbox_get_text(ui->Music_list_msgbox_1), &style_Music_list_msgbox_1_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_1_extra_btns_items_default
            static lv_style_t style_Music_list_msgbox_1_extra_btns_items_default;
            ui_init_style(&style_Music_list_msgbox_1_extra_btns_items_default);

            lv_style_set_bg_opa(&style_Music_list_msgbox_1_extra_btns_items_default, 255);
            lv_style_set_bg_color(&style_Music_list_msgbox_1_extra_btns_items_default, lv_color_hex(0xe6e6e6));
            lv_style_set_border_width(&style_Music_list_msgbox_1_extra_btns_items_default, 0);
            lv_style_set_radius(&style_Music_list_msgbox_1_extra_btns_items_default, 10);
            lv_style_set_text_color(&style_Music_list_msgbox_1_extra_btns_items_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_1_extra_btns_items_default, &lv_font_simsun_16_cjk);
            lv_obj_add_style(lv_msgbox_get_btns(ui->Music_list_msgbox_1), &style_Music_list_msgbox_1_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

            break;

        case My_UI.Music_List_Prompt_Play_Music_Fail:
            // Write codes Music_list_msgbox_2
            static const char *Music_list_msgbox_2_btns[] = {"Close", ""};
            ui->Music_list_msgbox_2 = lv_msgbox_create(ui->Music_list, "Failed to play music file", "Please check if the SD card is inserted!\n", Music_list_msgbox_2_btns, false);
            lv_obj_set_size(lv_msgbox_get_btns(ui->Music_list_msgbox_2), 200, 30);
            lv_obj_set_pos(ui->Music_list_msgbox_2, 20, 30);
            lv_obj_set_size(ui->Music_list_msgbox_2, 200, 175);
            lv_obj_set_scrollbar_mode(ui->Music_list_msgbox_2, LV_SCROLLBAR_MODE_OFF);

            // Write style for Music_list_msgbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
            lv_obj_set_style_bg_opa(ui->Music_list_msgbox_2, 230, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(ui->Music_list_msgbox_2, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(ui->Music_list_msgbox_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(ui->Music_list_msgbox_2, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_width(ui->Music_list_msgbox_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_2_extra_title_main_default
            static lv_style_t style_Music_list_msgbox_2_extra_title_main_default;
            ui_init_style(&style_Music_list_msgbox_2_extra_title_main_default);

            lv_style_set_text_color(&style_Music_list_msgbox_2_extra_title_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_2_extra_title_main_default, &lv_font_simsun_16_cjk);
            lv_style_set_text_letter_space(&style_Music_list_msgbox_2_extra_title_main_default, 0);
            lv_style_set_text_line_space(&style_Music_list_msgbox_2_extra_title_main_default, 30);
            lv_obj_add_style(lv_msgbox_get_title(ui->Music_list_msgbox_2), &style_Music_list_msgbox_2_extra_title_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_2_extra_content_main_default
            static lv_style_t style_Music_list_msgbox_2_extra_content_main_default;
            ui_init_style(&style_Music_list_msgbox_2_extra_content_main_default);

            lv_style_set_text_color(&style_Music_list_msgbox_2_extra_content_main_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_2_extra_content_main_default, &lv_font_simsun_16_cjk);
            lv_style_set_text_letter_space(&style_Music_list_msgbox_2_extra_content_main_default, 0);
            lv_style_set_text_line_space(&style_Music_list_msgbox_2_extra_content_main_default, 10);
            lv_obj_add_style(lv_msgbox_get_text(ui->Music_list_msgbox_2), &style_Music_list_msgbox_2_extra_content_main_default, LV_PART_MAIN | LV_STATE_DEFAULT);

            // Write style state: LV_STATE_DEFAULT for &style_Music_list_msgbox_2_extra_btns_items_default
            static lv_style_t style_Music_list_msgbox_2_extra_btns_items_default;
            ui_init_style(&style_Music_list_msgbox_2_extra_btns_items_default);

            lv_style_set_bg_opa(&style_Music_list_msgbox_2_extra_btns_items_default, 255);
            lv_style_set_bg_color(&style_Music_list_msgbox_2_extra_btns_items_default, lv_color_hex(0xe6e6e6));
            lv_style_set_border_width(&style_Music_list_msgbox_2_extra_btns_items_default, 0);
            lv_style_set_radius(&style_Music_list_msgbox_2_extra_btns_items_default, 10);
            lv_style_set_text_color(&style_Music_list_msgbox_2_extra_btns_items_default, lv_color_hex(0x4e4e4e));
            lv_style_set_text_font(&style_Music_list_msgbox_2_extra_btns_items_default, &lv_font_simsun_16_cjk);
            lv_obj_add_style(lv_msgbox_get_btns(ui->Music_list_msgbox_2), &style_Music_list_msgbox_2_extra_btns_items_default, LV_PART_ITEMS | LV_STATE_DEFAULT);

            break;

        default:
            break;
        }
    }

    if (My_UI.Music_List_Total_Number == 0) // 如果没有歌曲
    {
        // Write codes Music_list_imgbtn_1
        ui->Music_list_imgbtn_1 = lv_imgbtn_create(ui->Music_list);
        lv_obj_add_flag(ui->Music_list_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
        lv_imgbtn_set_src(ui->Music_list_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_30_alpha_183x144, NULL);
        lv_imgbtn_set_src(ui->Music_list_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_29_alpha_183x144, NULL);
        lv_obj_add_flag(ui->Music_list_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
        ui->Music_list_imgbtn_1_label = lv_label_create(ui->Music_list_imgbtn_1);
        lv_label_set_text(ui->Music_list_imgbtn_1_label, "");
        lv_label_set_long_mode(ui->Music_list_imgbtn_1_label, LV_LABEL_LONG_WRAP);
        lv_obj_align(ui->Music_list_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_pad_all(ui->Music_list_imgbtn_1, 0, LV_STATE_DEFAULT);
        lv_obj_set_pos(ui->Music_list_imgbtn_1, 29, 70);
        lv_obj_set_size(ui->Music_list_imgbtn_1, 183, 144);
        lv_obj_set_scrollbar_mode(ui->Music_list_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

        // Write style for Music_list_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
        lv_obj_set_style_img_opa(ui->Music_list_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui->Music_list_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui->Music_list_imgbtn_1, &lv_font_simsun_16_cjk, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_align(ui->Music_list_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_shadow_width(ui->Music_list_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        // Write style for Music_list_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
        lv_obj_set_style_img_opa(ui->Music_list_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_color(ui->Music_list_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_text_font(ui->Music_list_imgbtn_1, &lv_font_simsun_16_cjk, LV_PART_MAIN | LV_STATE_PRESSED);
        lv_obj_set_style_shadow_width(ui->Music_list_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_PRESSED);

        // Write style for Music_list_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
        lv_obj_set_style_img_opa(ui->Music_list_imgbtn_1, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_color(ui->Music_list_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_text_font(ui->Music_list_imgbtn_1, &lv_font_simsun_16_cjk, LV_PART_MAIN | LV_STATE_CHECKED);
        lv_obj_set_style_shadow_width(ui->Music_list_imgbtn_1, 0, LV_PART_MAIN | LV_STATE_CHECKED);
    }

    // 刷新状态栏
    My_UI_Window_StatusBar(ui, ui->Music_list);

    // Update current screen layout.
    lv_obj_update_layout(ui->Music_list);

    // Init events for screen.
    events_init_Music_list(ui);
}
