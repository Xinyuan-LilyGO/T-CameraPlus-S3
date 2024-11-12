/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"

    typedef struct
    {
        lv_obj_t *Home;
        bool Home_del;
        lv_obj_t *Home_carousel_1;
        lv_obj_t *Home_carousel_1_element_1;
        lv_obj_t *Home_carousel_1_element_2;
        lv_obj_t *Home_carousel_1_element_3;
        lv_obj_t *Home_carousel_1_element_4;
        lv_obj_t *Home_carousel_1_element_5;
        lv_obj_t *Home_carousel_1_element_6;
        lv_obj_t *Home_btn_1;
        lv_obj_t *Home_btn_1_label;
        lv_obj_t *Home_label_1;
        lv_obj_t *Home_btn_2;
        lv_obj_t *Home_btn_2_label;
        lv_obj_t *Home_label_2;
        lv_obj_t *Home_btn_3;
        lv_obj_t *Home_btn_3_label;
        lv_obj_t *Home_label_3;
        lv_obj_t *Home_btn_4;
        lv_obj_t *Home_btn_4_label;
        lv_obj_t *Home_label_4;
        lv_obj_t *Home_btn_5;
        lv_obj_t *Home_btn_5_label;
        lv_obj_t *Home_label_5;
        lv_obj_t *Home_btn_6;
        lv_obj_t *Home_btn_6_label;
        lv_obj_t *Home_label_6;
        lv_obj_t *Home_cont_1;
        lv_obj_t *Home_digital_clock_1;
        lv_obj_t *Home_label_8;

        lv_obj_t *Playing;
        bool Playing_del;
        lv_obj_t *Playing_imgbtn_1;
        lv_obj_t *Playing_imgbtn_1_label;
        lv_obj_t *Playing_imgbtn_2;
        lv_obj_t *Playing_imgbtn_2_label;
        lv_obj_t *Playing_imgbtn_3;
        lv_obj_t *Playing_imgbtn_3_label;
        lv_obj_t *Playing_cont_2;
        lv_obj_t *Playing_slider_1;
        lv_obj_t *Playing_imgbtn_4;
        lv_obj_t *Playing_imgbtn_4_label;
        lv_obj_t *Playing_slider_2;
        lv_obj_t *Playing_imgbtn_5;
        lv_obj_t *Playing_imgbtn_5_label;
        lv_obj_t *Playing_imgbtn_6;
        lv_obj_t *Playing_imgbtn_6_label;
        lv_obj_t *Playing_imgbtn_7;
        lv_obj_t *Playing_imgbtn_7_label;
        lv_obj_t *Playing_label_1;
        lv_obj_t *Playing_slider_3;
        lv_obj_t *Playing_label_2;
        lv_obj_t *Playing_label_3;
        lv_obj_t *Playing_label_4;

        lv_obj_t *My_Music;
        bool My_Music_del;
        lv_obj_t *My_Music_list_1;
        lv_obj_t *My_Music_list_1_item0;
        lv_obj_t *My_Music_list_1_item1;
        lv_obj_t *My_Music_list_1_item2;
        lv_obj_t *Settings;
        bool Settings_del;
        lv_obj_t *Settings_list_1;
        lv_obj_t *Settings_list_1_item0;
        lv_obj_t *Settings_list_1_item1;
        lv_obj_t *Settings_list_1_item2;
        lv_obj_t *Settings_list_1_item3;
        lv_obj_t *Settings_list_1_item4;
        lv_obj_t *Settings_list_1_item5;
        lv_obj_t *Camera;
        bool Camera_del;
        lv_obj_t *Recorder;
        bool Recorder_del;

        lv_obj_t *Explorer;
        bool Explorer_del;
        lv_obj_t *Explorer_list_1;
        lv_obj_t *Explorer_list_1_item0;
        lv_obj_t *Explorer_imgbtn_1;
        lv_obj_t *Explorer_imgbtn_1_label;

        lv_obj_t *Music_list;
        bool Music_list_del;
        lv_obj_t *Music_list_list_1;
        lv_obj_t *Music_list_list_1_item0;
        lv_obj_t *Music_list_imgbtn_1;
        lv_obj_t *Music_list_imgbtn_1_label;
        lv_obj_t *Music_list_msgbox_1;
        lv_obj_t *Music_list_msgbox_2;
        lv_obj_t *Music_file_scanning;
        bool Music_file_scanning_del;
        lv_obj_t *Music_file_scanning_list_1;
        lv_obj_t *Music_file_scanning_list_1_item0;
        lv_obj_t *Music_file_scanning_btnm_1;
        lv_obj_t *Music_file_scanning_imgbtn_1;
        lv_obj_t *Music_file_scanning_imgbtn_1_label;
        lv_obj_t *Music_file_scanning_msgbox_1;
        lv_obj_t *Music_file_scanning_msgbox_2;
    } lv_ui;

    void ui_init_style(lv_style_t *style);
    void init_scr_del_flag(lv_ui *ui);
    void setup_ui(lv_ui *ui);
    extern lv_ui guider_ui;

    void setup_scr_Home(lv_ui *ui);
    void setup_scr_Playing(lv_ui *ui);
    void setup_scr_My_Music(lv_ui *ui);
    void setup_scr_Settings(lv_ui *ui);
    void setup_scr_Camera(lv_ui *ui);
    void setup_scr_Recorder(lv_ui *ui);
    void setup_scr_Explorer(lv_ui *ui);
    void setup_scr_Music_list(lv_ui *ui);
    void setup_scr_Music_file_scanning(lv_ui *ui);

    LV_IMG_DECLARE(_1_140x140);

    LV_IMG_DECLARE(_2_140x140);

    LV_IMG_DECLARE(_15_140x140);

    LV_IMG_DECLARE(_24_140x140);

    LV_IMG_DECLARE(_25_140x140);

    LV_IMG_DECLARE(_26_140x140);
    LV_IMG_DECLARE(_9_alpha_60x60);
    LV_IMG_DECLARE(_10_alpha_60x60);
    LV_IMG_DECLARE(_7_alpha_60x60);
    LV_IMG_DECLARE(_8_alpha_60x60);
    LV_IMG_DECLARE(_11_alpha_30x30);
    LV_IMG_DECLARE(_12_alpha_30x30);
    LV_IMG_DECLARE(_13_alpha_30x30);
    LV_IMG_DECLARE(_14_alpha_30x30);
    LV_IMG_DECLARE(_16_alpha_50x50);
    LV_IMG_DECLARE(_18_alpha_50x50);
    LV_IMG_DECLARE(_20_alpha_50x50);
    LV_IMG_DECLARE(_17_alpha_50x50);
    LV_IMG_DECLARE(_19_alpha_50x50);
    LV_IMG_DECLARE(_21_alpha_50x50);
    LV_IMG_DECLARE(_22_alpha_30x30);
    LV_IMG_DECLARE(_23_alpha_27x27);
    LV_IMG_DECLARE(_28_alpha_168x168);
    LV_IMG_DECLARE(_27_alpha_168x168);
    LV_IMG_DECLARE(_30_alpha_183x144);
    LV_IMG_DECLARE(_29_alpha_183x144);

    LV_FONT_DECLARE(lv_font_simsun_18)
    LV_FONT_DECLARE(lv_font_montserratMedium_16)
    LV_FONT_DECLARE(lv_font_montserratMedium_12)
    LV_FONT_DECLARE(lv_font_arial_16)
    LV_FONT_DECLARE(lv_font_FontAwesome5_16)
    LV_FONT_DECLARE(lv_font_FontAwesome5_18)
    LV_FONT_DECLARE(lv_font_montserratMedium_18)
    LV_FONT_DECLARE(lv_font_arial_12)
    LV_FONT_DECLARE(lv_font_arial_14)

#ifdef __cplusplus
}
#endif
#endif
