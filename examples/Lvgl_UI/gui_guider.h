/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 11:22:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 11:13:14
 * @License: GPL 3.0
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
        // 全窗口使用
        lv_obj_t *Window_StatusBar_cont_1;
        lv_obj_t *Window_StatusBar_digital_clock_1;
        lv_obj_t *Window_StatusBar_label_1;

        lv_obj_t *Window_StatusBar_Expand_cont_2;
        lv_obj_t *Window_StatusBar_Expand_slider_1;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_4;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_4_label;
        lv_obj_t *Window_StatusBar_Expand_slider_2;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_5;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_5_label;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_6;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_6_label;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_7;
        lv_obj_t *Window_StatusBar_Expand_imgbtn_7_label;

        // 部分窗口使用
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

        lv_obj_t *Playing;
        bool Playing_del;
        lv_obj_t *Playing_imgbtn_1;
        lv_obj_t *Playing_imgbtn_1_label;
        lv_obj_t *Playing_imgbtn_2;
        lv_obj_t *Playing_imgbtn_2_label;
        lv_obj_t *Playing_imgbtn_3;
        lv_obj_t *Playing_imgbtn_3_label;
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

        lv_obj_t *Camera_Wifi;
        bool Camera_Wifi_del;
        lv_obj_t *Camera_Wifi_win_1;
        lv_obj_t *Camera_Wifi_btnm_1;

        lv_obj_t *Recorder;
        bool Recorder_del;
        lv_obj_t *Recorder_win_1;
        lv_obj_t *Recorder_btnm_1;

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

        lv_obj_t *Battery;
        bool Battery_del;
        lv_obj_t *g_kb_Battery;
        lv_obj_t *Battery_tabview_1;
        lv_obj_t *Battery_tabview_1_tab_1;
        lv_obj_t *Battery_tabview_1_tab_2;
        lv_obj_t *Battery_table_1;
        lv_obj_t *Battery_table_2;
        lv_obj_t *Battery_ta_1;
        lv_obj_t *Battery_ta_2;
        lv_obj_t *Battery_ta_3;
        lv_obj_t *Battery_ta_4;
        lv_obj_t *Battery_sw_1;
        lv_obj_t *Battery_msgbox_1;

        lv_obj_t *WIFI;
        bool WIFI_del;
        lv_obj_t *g_kb_WIFI;
        lv_obj_t *WIFI_list_1;
        lv_obj_t *WIFI_sw_1;
        lv_obj_t *WIFI_label_1;
        lv_obj_t *WIFI_msgbox_1;
        lv_obj_t *WIFI_ta_1;
        lv_obj_t *WIFI_msgbox_2;
        lv_obj_t *WIFI_msgbox_3;

        lv_obj_t *Camera;
        bool Camera_del;
        lv_obj_t *Camera_btnm_1;
        lv_obj_t *Camera_label_1;

        lv_obj_t *Camera_Screen;
        bool Camera_Screen_del;
    } lv_ui;

    void ui_init_style(lv_style_t *style);
    void init_scr_del_flag(lv_ui *ui);
    void setup_ui(lv_ui *ui);
    extern lv_ui guider_ui;

    void setup_scr_Home(lv_ui *ui);
    void setup_scr_Playing(lv_ui *ui);
    void setup_scr_My_Music(lv_ui *ui);
    void setup_scr_Settings(lv_ui *ui);
    void setup_scr_Camera_Wifi(lv_ui *ui);
    void setup_scr_Recorder(lv_ui *ui);
    void setup_scr_Explorer(lv_ui *ui);
    void setup_scr_Music_list(lv_ui *ui);
    void setup_scr_Music_file_scanning(lv_ui *ui);
    void setup_scr_Battery(lv_ui *ui);
    void setup_scr_WIFI(lv_ui *ui);
    void setup_scr_Camera(lv_ui *ui);
    void setup_scr_Camera_Screen(lv_ui *ui);

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
