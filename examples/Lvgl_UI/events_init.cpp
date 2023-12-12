/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 11:22:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-07 17:51:09
 * @License: GPL 3.0
 */
#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "SY6970.h"
#include "MSM261.h"

static void Window_StatusBar_slider_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        My_UI.System_Volume = lv_slider_get_value(guider_ui.Window_StatusBar_Expand_slider_1);
        audio.setVolume(My_UI.System_Volume); // 0...21,Volume setting
        break;
    }
    default:
        break;
    }
}
static void Window_StatusBar_slider_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        My_UI.System_Screen_Brightness = lv_slider_get_value(guider_ui.Window_StatusBar_Expand_slider_2);
        ledcWrite(1, My_UI.System_Screen_Brightness); // brightness 0 - 255
        break;
    }
    default:
        break;
    }
}

static void Home_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_set_height(guider_ui.Window_StatusBar_Expand_cont_2, 0);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_obj_add_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 0);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            lv_obj_clear_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Home_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Playing_del == true)
            {
                setup_scr_Playing(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Playing, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Playing_del = true;
        }
        // Write animation: Home_btn_1 move in x direction
        lv_anim_t Home_btn_1_anim_x;
        lv_anim_init(&Home_btn_1_anim_x);
        lv_anim_set_var(&Home_btn_1_anim_x, guider_ui.Home_btn_1);
        lv_anim_set_time(&Home_btn_1_anim_x, 300);
        lv_anim_set_delay(&Home_btn_1_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_1_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_1_anim_x, lv_obj_get_x(guider_ui.Home_btn_1), 15);
        lv_anim_set_path_cb(&Home_btn_1_anim_x, &lv_anim_path_ease_in);
        Home_btn_1_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_1_anim_x);
        // Write animation: Home_btn_1 move in y direction
        lv_anim_t Home_btn_1_anim_y;
        lv_anim_init(&Home_btn_1_anim_y);
        lv_anim_set_var(&Home_btn_1_anim_y, guider_ui.Home_btn_1);
        lv_anim_set_time(&Home_btn_1_anim_y, 300);
        lv_anim_set_delay(&Home_btn_1_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_1_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_1_anim_y, lv_obj_get_y(guider_ui.Home_btn_1), -300);
        lv_anim_set_path_cb(&Home_btn_1_anim_y, &lv_anim_path_ease_in);
        Home_btn_1_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_1_anim_y);
        break;
    }
    default:
        break;
    }
}
static void Home_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.My_Music_del == true)
            {
                setup_scr_My_Music(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.My_Music_del = true;
        }
        // Write animation: Home_btn_2 move in x direction
        lv_anim_t Home_btn_2_anim_x;
        lv_anim_init(&Home_btn_2_anim_x);
        lv_anim_set_var(&Home_btn_2_anim_x, guider_ui.Home_btn_2);
        lv_anim_set_time(&Home_btn_2_anim_x, 300);
        lv_anim_set_delay(&Home_btn_2_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_2_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_2_anim_x, lv_obj_get_x(guider_ui.Home_btn_2), 15);
        lv_anim_set_path_cb(&Home_btn_2_anim_x, &lv_anim_path_linear);
        Home_btn_2_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_2_anim_x);
        // Write animation: Home_btn_2 move in y direction
        lv_anim_t Home_btn_2_anim_y;
        lv_anim_init(&Home_btn_2_anim_y);
        lv_anim_set_var(&Home_btn_2_anim_y, guider_ui.Home_btn_2);
        lv_anim_set_time(&Home_btn_2_anim_y, 300);
        lv_anim_set_delay(&Home_btn_2_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_2_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_2_anim_y, lv_obj_get_y(guider_ui.Home_btn_2), -300);
        lv_anim_set_path_cb(&Home_btn_2_anim_y, &lv_anim_path_linear);
        Home_btn_2_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_2_anim_y);
        break;
    }
    default:
        break;
    }
}
static void Home_btn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Settings_del == true)
            {
                setup_scr_Settings(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Settings_del = true;
        }
        // Write animation: Home_btn_3 move in x direction
        lv_anim_t Home_btn_3_anim_x;
        lv_anim_init(&Home_btn_3_anim_x);
        lv_anim_set_var(&Home_btn_3_anim_x, guider_ui.Home_btn_3);
        lv_anim_set_time(&Home_btn_3_anim_x, 300);
        lv_anim_set_delay(&Home_btn_3_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_3_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_3_anim_x, lv_obj_get_x(guider_ui.Home_btn_3), 15);
        lv_anim_set_path_cb(&Home_btn_3_anim_x, &lv_anim_path_linear);
        Home_btn_3_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_3_anim_x);
        // Write animation: Home_btn_3 move in y direction
        lv_anim_t Home_btn_3_anim_y;
        lv_anim_init(&Home_btn_3_anim_y);
        lv_anim_set_var(&Home_btn_3_anim_y, guider_ui.Home_btn_3);
        lv_anim_set_time(&Home_btn_3_anim_y, 300);
        lv_anim_set_delay(&Home_btn_3_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_3_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_3_anim_y, lv_obj_get_y(guider_ui.Home_btn_3), -300);
        lv_anim_set_path_cb(&Home_btn_3_anim_y, &lv_anim_path_linear);
        Home_btn_3_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_3_anim_y);
        break;
    }
    default:
        break;
    }
}
static void Home_btn_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Camera_del == true)
            {
                setup_scr_Camera(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Camera, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Camera_del = true;
        }
        // Write animation: Home_btn_4 move in x direction
        lv_anim_t Home_btn_4_anim_x;
        lv_anim_init(&Home_btn_4_anim_x);
        lv_anim_set_var(&Home_btn_4_anim_x, guider_ui.Home_btn_4);
        lv_anim_set_time(&Home_btn_4_anim_x, 300);
        lv_anim_set_delay(&Home_btn_4_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_4_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_4_anim_x, lv_obj_get_x(guider_ui.Home_btn_4), 15);
        lv_anim_set_path_cb(&Home_btn_4_anim_x, &lv_anim_path_linear);
        Home_btn_4_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_4_anim_x);
        // Write animation: Home_btn_4 move in y direction
        lv_anim_t Home_btn_4_anim_y;
        lv_anim_init(&Home_btn_4_anim_y);
        lv_anim_set_var(&Home_btn_4_anim_y, guider_ui.Home_btn_4);
        lv_anim_set_time(&Home_btn_4_anim_y, 300);
        lv_anim_set_delay(&Home_btn_4_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_4_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_4_anim_y, lv_obj_get_y(guider_ui.Home_btn_4), -300);
        lv_anim_set_path_cb(&Home_btn_4_anim_y, &lv_anim_path_linear);
        Home_btn_4_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_4_anim_y);

        break;
    }
    default:
        break;
    }
}
static void Home_btn_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // My_UI.MSM261_Recording_Text.clear();

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Recorder_del == true)
            {
                setup_scr_Recorder(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Recorder, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Recorder_del = true;
        }
        // Write animation: Home_btn_5 move in x direction
        lv_anim_t Home_btn_5_anim_x;
        lv_anim_init(&Home_btn_5_anim_x);
        lv_anim_set_var(&Home_btn_5_anim_x, guider_ui.Home_btn_5);
        lv_anim_set_time(&Home_btn_5_anim_x, 300);
        lv_anim_set_delay(&Home_btn_5_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_5_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_5_anim_x, lv_obj_get_x(guider_ui.Home_btn_5), 15);
        lv_anim_set_path_cb(&Home_btn_5_anim_x, &lv_anim_path_ease_in);
        Home_btn_5_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_5_anim_x);
        // Write animation: Home_btn_5 move in y direction
        lv_anim_t Home_btn_5_anim_y;
        lv_anim_init(&Home_btn_5_anim_y);
        lv_anim_set_var(&Home_btn_5_anim_y, guider_ui.Home_btn_5);
        lv_anim_set_time(&Home_btn_5_anim_y, 300);
        lv_anim_set_delay(&Home_btn_5_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_5_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_5_anim_y, lv_obj_get_y(guider_ui.Home_btn_5), -300);
        lv_anim_set_path_cb(&Home_btn_5_anim_y, &lv_anim_path_ease_in);
        Home_btn_5_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_5_anim_y);

        break;
    }
    default:
        break;
    }
}
static void Home_btn_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Explorer_del == true)
            {
                setup_scr_Explorer(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Explorer, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Explorer_del = true;
        }
        // Write animation: Home_btn_6 move in x direction
        lv_anim_t Home_btn_6_anim_x;
        lv_anim_init(&Home_btn_6_anim_x);
        lv_anim_set_var(&Home_btn_6_anim_x, guider_ui.Home_btn_6);
        lv_anim_set_time(&Home_btn_6_anim_x, 300);
        lv_anim_set_delay(&Home_btn_6_anim_x, 0);
        lv_anim_set_exec_cb(&Home_btn_6_anim_x, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&Home_btn_6_anim_x, lv_obj_get_x(guider_ui.Home_btn_6), 15);
        lv_anim_set_path_cb(&Home_btn_6_anim_x, &lv_anim_path_ease_in);
        Home_btn_6_anim_x.repeat_cnt = 0;
        lv_anim_start(&Home_btn_6_anim_x);
        // Write animation: Home_btn_6 move in y direction
        lv_anim_t Home_btn_6_anim_y;
        lv_anim_init(&Home_btn_6_anim_y);
        lv_anim_set_var(&Home_btn_6_anim_y, guider_ui.Home_btn_6);
        lv_anim_set_time(&Home_btn_6_anim_y, 300);
        lv_anim_set_delay(&Home_btn_6_anim_y, 0);
        lv_anim_set_exec_cb(&Home_btn_6_anim_y, (lv_anim_exec_xcb_t)lv_obj_set_y);
        lv_anim_set_values(&Home_btn_6_anim_y, lv_obj_get_y(guider_ui.Home_btn_6), -300);
        lv_anim_set_path_cb(&Home_btn_6_anim_y, &lv_anim_path_ease_in);
        Home_btn_6_anim_y.repeat_cnt = 0;
        lv_anim_start(&Home_btn_6_anim_y);
        break;
    }
    default:
        break;
    }
}
void events_init_Home(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Home, Home_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_1, Home_btn_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_2, Home_btn_2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_3, Home_btn_3_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_4, Home_btn_4_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_5, Home_btn_5_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_6, Home_btn_6_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_1, Window_StatusBar_slider_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_2, Window_StatusBar_slider_2_event_handler, LV_EVENT_ALL, NULL);
}
static void Playing_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_set_height(guider_ui.Window_StatusBar_Expand_cont_2, 0);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_obj_add_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 0);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            lv_obj_clear_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Playing_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        My_UI.Playing_Current_Static = !My_UI.Playing_Current_Static;

        break;
    }
    default:
        break;
    }
}

static void Playing_imgbtn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.SD_Initialization_Flag == true)
        {
            if (My_UI.Music_List_Total_Number != 0)
            {
                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Switch; // 设置播放状态为切换状态
                My_UI.Playing_Current_Music_File_Duration = 0;                      // 设置当前的音乐文件时间为0
                My_UI.Playing_Current_Music_Time = 0;                               // 设置当前的音乐已经播放了的时间为0

                My_UI.Music_List_Current_Number++; // 将当前播放列表音乐号数+1

                // 判断当前播放列表是否溢出，如果溢出从头开始（+1是因为当前音乐从0开始算的）
                if ((My_UI.Music_List_Current_Number + 1) > My_UI.Music_List_Total_Number)
                {
                    My_UI.Music_List_Current_Number = 0;
                }

                My_UI.Playing_Current_Music_Name.clear(); // 清除上一次的音乐文件信息
                // 刷新当前音乐文件名字
                My_UI.Playing_Current_Music_Name = My_UI.Music_List_File[My_UI.Music_List_Current_Number].file_name;

                // Write the load screen code.
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Playing_del == true)
                    {
                        setup_scr_Playing(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Playing, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                    guider_ui.Playing_del = true;
                }

                // 开启动画延时
                // 等待lvgl渲染完播放界面画面在加载歌曲，否则会造成花屏
                My_UI.Playing_Load_Anim_Delay_Flag = My_UI.Playing_Load_Anim_Delay_ON;
            }
        }
        break;
    }
    default:
        break;
    }
}

static void Playing_imgbtn_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.SD_Initialization_Flag == true)
        {
            if (My_UI.Music_List_Total_Number != 0)
            {
                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Switch; // 设置播放状态为切换状态
                My_UI.Playing_Current_Music_File_Duration = 0;                      // 设置当前的音乐文件时间为0
                My_UI.Playing_Current_Music_Time = 0;                               // 设置当前的音乐已经播放了的时间为0

                My_UI.Music_List_Current_Number--; // 将当前播放列表音乐号数-1

                // 判断当前播放列表是否溢出，如果溢出从头开始（+1是因为当前音乐从0开始算的）
                if ((My_UI.Music_List_Current_Number + 1) <= 0)
                {
                    My_UI.Music_List_Current_Number = My_UI.Music_List_Total_Number - 1;
                }

                My_UI.Playing_Current_Music_Name.clear(); // 清除上一次的音乐文件信息
                // 刷新当前音乐文件名字
                My_UI.Playing_Current_Music_Name = My_UI.Music_List_File[My_UI.Music_List_Current_Number].file_name;

                // Write the load screen code.
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Playing_del == true)
                    {
                        setup_scr_Playing(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Playing, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                    guider_ui.Playing_del = true;
                }

                // 开启动画延时
                // 等待lvgl渲染完播放界面画面在加载歌曲，否则会造成花屏
                My_UI.Playing_Load_Anim_Delay_Flag = My_UI.Playing_Load_Anim_Delay_ON;
            }
        }

        break;
    }
    default:
        break;
    }
}
void events_init_Playing(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Playing, Playing_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Playing_imgbtn_1, Playing_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Playing_imgbtn_2, Playing_imgbtn_2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Playing_imgbtn_3, Playing_imgbtn_3_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_1, Window_StatusBar_slider_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_2, Window_StatusBar_slider_2_event_handler, LV_EVENT_ALL, NULL);
}
static void My_Music_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void My_Music_list_1_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_list_del == true)
            {
                setup_scr_Music_list(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_list, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_list_del = true;
        }
        break;
    }
    default:
        break;
    }
}
static void My_Music_list_1_item1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_file_scanning_del == true)
            {
                setup_scr_Music_file_scanning(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_file_scanning_del = true;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_My_Music(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->My_Music, My_Music_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->My_Music_list_1_item0, My_Music_list_1_item0_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->My_Music_list_1_item1, My_Music_list_1_item1_event_handler, LV_EVENT_ALL, NULL);
}
static void Settings_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_set_height(guider_ui.Window_StatusBar_Expand_cont_2, 0);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_obj_add_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_TOP:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 0);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_out);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            lv_obj_clear_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
            // Write animation: window_statusbar_cont_2 scale in width
            lv_anim_t window_statusbar_cont_2_anim_width;
            lv_anim_init(&window_statusbar_cont_2_anim_width);
            lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_width);
            // Write animation: window_statusbar_cont_2 scale in height
            lv_anim_t window_statusbar_cont_2_anim_height;
            lv_anim_init(&window_statusbar_cont_2_anim_height);
            lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
            lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
            lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 240);
            lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_in);
            window_statusbar_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&window_statusbar_cont_2_anim_height);
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}

static void Settings_list_1_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.WIFI_del == true)
            {
                setup_scr_WIFI(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.WIFI_del = true;
        }
        break;
    }
    default:
        break;
    }
}
static void Settings_list_1_item2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        lv_obj_clear_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
        // Write animation: window_statusbar_cont_2 scale in width
        lv_anim_t window_statusbar_cont_2_anim_width;
        lv_anim_init(&window_statusbar_cont_2_anim_width);
        lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
        lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
        lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
        lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
        lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
        lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_in);
        window_statusbar_cont_2_anim_width.repeat_cnt = 0;
        lv_anim_start(&window_statusbar_cont_2_anim_width);
        // Write animation: window_statusbar_cont_2 scale in height
        lv_anim_t window_statusbar_cont_2_anim_height;
        lv_anim_init(&window_statusbar_cont_2_anim_height);
        lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
        lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
        lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
        lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
        lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 240);
        lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_in);
        window_statusbar_cont_2_anim_height.repeat_cnt = 0;
        lv_anim_start(&window_statusbar_cont_2_anim_height);
        break;
    }
    default:
        break;
    }
}
static void Settings_list_1_item3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        lv_obj_clear_flag(guider_ui.Window_StatusBar_Expand_cont_2, LV_OBJ_FLAG_HIDDEN);
        // Write animation: window_statusbar_cont_2 scale in width
        lv_anim_t window_statusbar_cont_2_anim_width;
        lv_anim_init(&window_statusbar_cont_2_anim_width);
        lv_anim_set_var(&window_statusbar_cont_2_anim_width, guider_ui.Window_StatusBar_Expand_cont_2);
        lv_anim_set_time(&window_statusbar_cont_2_anim_width, 500);
        lv_anim_set_delay(&window_statusbar_cont_2_anim_width, 0);
        lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
        lv_anim_set_values(&window_statusbar_cont_2_anim_width, lv_obj_get_width(guider_ui.Window_StatusBar_Expand_cont_2), 240);
        lv_anim_set_path_cb(&window_statusbar_cont_2_anim_width, &lv_anim_path_ease_in);
        window_statusbar_cont_2_anim_width.repeat_cnt = 0;
        lv_anim_start(&window_statusbar_cont_2_anim_width);
        // Write animation: window_statusbar_cont_2 scale in height
        lv_anim_t window_statusbar_cont_2_anim_height;
        lv_anim_init(&window_statusbar_cont_2_anim_height);
        lv_anim_set_var(&window_statusbar_cont_2_anim_height, guider_ui.Window_StatusBar_Expand_cont_2);
        lv_anim_set_time(&window_statusbar_cont_2_anim_height, 500);
        lv_anim_set_delay(&window_statusbar_cont_2_anim_height, 0);
        lv_anim_set_exec_cb(&window_statusbar_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
        lv_anim_set_values(&window_statusbar_cont_2_anim_height, lv_obj_get_height(guider_ui.Window_StatusBar_Expand_cont_2), 240);
        lv_anim_set_path_cb(&window_statusbar_cont_2_anim_height, &lv_anim_path_ease_in);
        window_statusbar_cont_2_anim_height.repeat_cnt = 0;
        lv_anim_start(&window_statusbar_cont_2_anim_height);
        break;
    }
    default:
        break;
    }
}
static void Settings_list_1_item4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        if (SY6970_Initialization() == true)
        {
            My_UI.Battery_Information_Refresh_Flag = true;
        }
        else
        {
            My_UI.Battery_Information_Refresh_Flag = false;
        }

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Battery_del == true)
            {
                setup_scr_Battery(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Battery, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Battery_del = true;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Settings(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Settings, Settings_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Settings_list_1_item0, Settings_list_1_item0_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Settings_list_1_item2, Settings_list_1_item2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Settings_list_1_item3, Settings_list_1_item3_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Settings_list_1_item4, Settings_list_1_item4_event_handler, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_1, Window_StatusBar_slider_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Window_StatusBar_Expand_slider_2, Window_StatusBar_slider_2_event_handler, LV_EVENT_ALL, NULL);
}
static void Camera_Wifi_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_del == true)
                {
                    setup_scr_Camera(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Camera_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Camera_Wifi_btnm_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        switch (id)
        {
        case 0:
        {
            // if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
            // {
            //     if (OV2640_Initialization() == true)
            //     {
            //         startCameraServer();

            //         Serial.print("Camera Ready! Use 'http://");
            //         Serial.print(WiFi.localIP());
            //         Serial.println("' to connect");
            //     }
            // }
            String text;
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            lv_obj_t *Camera_win_1_label = lv_label_create(lv_win_get_content(guider_ui.Camera_Wifi_win_1));

            My_UI.Camera_Device_Connect++;
            if (My_UI.Camera_Device_Connect > 2)
            {
                My_UI.Camera_Device_Connect = 0;
            }

            switch (My_UI.Camera_Device_Connect)
            {
            case My_UI.Camera_Device_Connect_OFF:
                // 刷新屏幕
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Camera_Wifi_del == true)
                    {
                        setup_scr_Camera_Wifi(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Camera_Wifi, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                    guider_ui.Camera_Wifi_del = true;
                }

                break;
            case My_UI.Camera_Device_Connect_WIFI:
                text = Camera_WIFI_Test();
                break;
            case My_UI.Camera_Device_Connect_OV2640:

                if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
                {
                    if (My_UI.Camera_Device_Status == true)
                    {
                        startCameraServer();

                        text = "Camera Ready! Use: \n 'http://";

                        switch (My_UI.Window_Camera_Wifi_Mode)
                        {
                        case My_UI.Camera_Wifi_Mode::Camera_Wifi_Mode_STA:
                            text += (WiFi.localIP()).toString();
                            break;
                        case My_UI.Camera_Wifi_Mode::Camera_Wifi_Mode_SoftAP:
                            text += (WiFi.softAPIP()).toString();
                            break;

                        default:
                            break;
                        }
                        text += "' to connect";
                    }

                    if (My_UI.Camera_Device_Status == false)
                    {
                        text += "Camera init failed with error";
                    }
                }

                if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_OFF)
                {
                }
                break;

            default:
                break;
            }

            lv_label_set_text(Camera_win_1_label, text.c_str());
            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Camera_Wifi);

            break;
        }
        case 1:
        {
            My_UI.KEY1_Change = true;
            My_UI.KEY1_Flag = !My_UI.KEY1_Flag;
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Camera_Wifi(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Camera_Wifi, Camera_Wifi_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Camera_Wifi_btnm_1, Camera_Wifi_btnm_1_event_handler, LV_EVENT_ALL, NULL);
}
static void Recorder_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}

static void Recorder_btnm_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        switch (id)
        {
        case 0:
        {
            My_UI.MSM261_Recording_Text.clear();
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Recorder_del == true)
                {
                    setup_scr_Recorder(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Recorder, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Recorder_del = true;
            }
            break;
        }
        case 1:
        {
            My_UI.MSM261_Recording_Text.c_str();
            lv_obj_t *Recorder_win_1_label = lv_label_create(lv_win_get_content(guider_ui.Recorder_win_1));

            SD_Initialization();

            if (My_UI.SD_Initialization_Flag == true)
            {
                if (My_UI.MSM261_Initialization_Flag == true)
                {

                    My_UI.MSM261_Recording_Text += "MSM261 initialization successful\n";
                    My_UI.MSM261_Recording_Text += "Start recording for 10 seconds\n";

                    My_UI.MSM261_Recording_Flag = My_UI.MSM261_Recording_ON;
                }
                else
                {
                    My_UI.MSM261_Recording_Text += "MSM261 initialization failed\n";
                }
            }
            else
            {
                My_UI.MSM261_Recording_Text = "SD card initialization failed";
            }

            lv_label_set_text(Recorder_win_1_label, (My_UI.MSM261_Recording_Text).c_str());
            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Recorder);

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Recorder(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Recorder, Recorder_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Recorder_btnm_1, Recorder_btnm_1_event_handler, LV_EVENT_ALL, NULL);
}
static void Explorer_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Explorer_list_1_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.AE_Current_Directory.back() == "/")
        {
        }
        else
        {
            My_UI.AE_Current_Directory.pop_back();

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Explorer_del == true)
                {
                    setup_scr_Explorer(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Explorer, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Explorer_del = true;
            }
        }
        break;
    }
    default:
        break;
    }
}
static void Explorer_list_1_folder_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Serial.printf("%d", e->user_data);
        // Serial.println(My_UI.AE_Folder_Name[(uint64_t)(e->user_data)]);

        My_UI.AE_Current_Directory.push_back(My_UI.AE_Folder_Name[(uint64_t)(e->user_data)]);

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Explorer_del == true)
            {
                setup_scr_Explorer(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Explorer, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Explorer_del = true;
        }
        break;
    }
    default:
        break;
    }
}
static void Explorer_list_1_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Serial.printf("%d", e->user_data);
        // Serial.println(My_UI.AE_File_Manager_S[(uint64_t)(e->user_data)].file_name + "   " + My_UI.AE_File_Manager_S[(uint64_t)(e->user_data)].file_size+"Kb");
        break;
    }
    default:
        break;
    }
}
static void Explorer_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        for (int i; i < 3; i++) // 循环扫描三次SD卡
        {
            if (SD_Initialization() == true)
            {
                break;
            }
            else
            {
            }
        }

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Explorer_del == true)
            {
                setup_scr_Explorer(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Explorer, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
            guider_ui.Explorer_del = true;
        }

        break;
    }
    default:
        break;
    }
}
void events_init_Explorer(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Explorer, Explorer_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Explorer_list_1_item0, Explorer_list_1_item0_event_handler, LV_EVENT_ALL, NULL);

    if (My_UI.SD_Initialization_Flag == true)
    {
        for (int i = 0; i < My_UI.AE_LV_List_Folder.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.AE_LV_List_Folder[i], Explorer_list_1_folder_event_handler, LV_EVENT_ALL, (void *)i);
        }
        for (int i = 0; i < My_UI.AE_LV_List_File.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.AE_LV_List_File[i], Explorer_list_1_file_event_handler, LV_EVENT_ALL, (void *)i);
        }
    }
    if (My_UI.SD_Initialization_Flag == false)
    {
        lv_obj_add_event_cb(ui->Explorer_imgbtn_1, Explorer_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
    }
}
static void Music_list_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.My_Music_del == true)
                {
                    setup_scr_My_Music(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.My_Music_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.My_Music_del == true)
                {
                    setup_scr_My_Music(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.My_Music_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Music_list_1_file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        My_UI.Music_List_Prompt_Flag = My_UI.Music_List_Prompt_Play_Music_Judgment;

        My_UI.Music_List_Current_Number = (uint64_t)(e->user_data);

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_list_del == true)
            {
                setup_scr_Music_list(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_list, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_list_del = true;
        }

        My_UI.Music_List_Prompt_Flag = My_UI.Music_List_Prompt_Normal; // 还原正常模式
        break;
    }
    default:
        break;
    }
}
static void Music_list_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_file_scanning_del == true)
            {
                setup_scr_Music_file_scanning(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_file_scanning_del = true;
        }
        break;
    }
    default:
        break;
    }
}
static void Music_list_msgbox_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_list_del == true)
                {
                    setup_scr_Music_list(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_list, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_list_del = true;
            }
            break;
        }
        case 1:
        {
            SD_Initialization();

            if (My_UI.SD_Initialization_Flag == true)
            {
                My_UI.Playing_Current_Music_Name.clear(); // 清除上一次的音乐文件信息
                // 刷新当前音乐文件名字
                My_UI.Playing_Current_Music_Name = My_UI.Music_List_File[My_UI.Music_List_Current_Number].file_name;

                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Switch; // 开始切换音乐

                // Write the load screen code.
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Playing_del == true)
                    {
                        setup_scr_Playing(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Playing, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                    guider_ui.Playing_del = true;
                }

                // 开启动画延时
                // 等待lvgl渲染完播放界面画面在加载歌曲，否则会造成花屏
                My_UI.Playing_Load_Anim_Delay_Flag = My_UI.Playing_Load_Anim_Delay_ON;
            }

            if (My_UI.SD_Initialization_Flag == false)
            {
                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Pause; // 暂停音乐

                My_UI.Music_List_Prompt_Flag = My_UI.Music_List_Prompt_Play_Music_Fail; // 错误信息标志

                // Write the load screen code.
                lv_obj_t *act_scr = lv_scr_act();
                lv_disp_t *d = lv_obj_get_disp(act_scr);
                if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
                {
                    if (guider_ui.Music_list_del == true)
                    {
                        setup_scr_Music_list(&guider_ui);
                    }
                    lv_scr_load_anim(guider_ui.Music_list, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                    guider_ui.Music_list_del = true;
                }
            }

            My_UI.Music_List_Prompt_Flag = My_UI.Music_List_Prompt_Normal; // 还原

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
static void Music_list_msgbox_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            My_UI.Music_List_Directory = {"/"};
            My_UI.Music_List_Total_Number = 0;
            My_UI.Music_List_Current_Number = 0;

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_list_del == true)
                {
                    setup_scr_Music_list(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_list, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_list_del = true;
            }

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Music_list(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Music_list, Music_list_event_handler, LV_EVENT_ALL, NULL);

    if (My_UI.Music_List_Total_Number != 0)
    {
        for (int i = 0; i < My_UI.AE_LV_List_File.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.AE_LV_List_File[i], Music_list_1_file_event_handler, LV_EVENT_ALL, (void *)i);
        }

        if (My_UI.Music_List_Prompt_Flag == My_UI.Music_List_Prompt_Play_Music_Judgment)
        {
            lv_obj_add_event_cb(ui->Music_list_msgbox_1, Music_list_msgbox_1_event_handler, LV_EVENT_ALL, NULL);
        }

        if (My_UI.Music_List_Prompt_Flag == My_UI.Music_List_Prompt_Play_Music_Fail)
        {
            lv_obj_add_event_cb(ui->Music_list_msgbox_2, Music_list_msgbox_2_event_handler, LV_EVENT_ALL, NULL);
        }
    }

    if (My_UI.Music_List_Total_Number == 0)
    {
        lv_obj_add_event_cb(ui->Music_list_imgbtn_1, Music_list_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
    }
}
static void Music_file_scanning_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.My_Music_del == true)
                {
                    setup_scr_My_Music(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.My_Music_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.My_Music_del == true)
                {
                    setup_scr_My_Music(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.My_Music_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Music_file_scanning_list_1_item0_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.Music_Scan_Directory.back() == "/")
        {
        }
        else
        {
            My_UI.Music_Scan_Directory.pop_back();

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_file_scanning_del == true)
                {
                    setup_scr_Music_file_scanning(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_file_scanning_del = true;
            }
        }

        break;
    }
    default:
        break;
    }
}

static void Music_file_scanning_list_1_folder_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        My_UI.Music_Scan_Directory.push_back(My_UI.AE_Folder_Name[(uint64_t)(e->user_data)]);

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_file_scanning_del == true)
            {
                setup_scr_Music_file_scanning(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_file_scanning_del = true;
        }

        break;
    }
    default:
        break;
    }
}
static void Music_file_scanning_btnm_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.My_Music_del == true)
                {
                    setup_scr_My_Music(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.My_Music, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.My_Music_del = true;
            }
            break;
        }
        case 1:
        {
            My_UI.Music_List_Directory = {"/"};
            My_UI.Music_List_Total_Number = 0;
            My_UI.Music_List_File.clear();

            AE_Class.File_Directory_Suffix_Scan(&SD, My_UI.Music_Scan_Directory, ".mp3", &My_UI.Music_List_File);
            AE_Class.File_Directory_Suffix_Scan(&SD, My_UI.Music_Scan_Directory, ".wav", &My_UI.Music_List_File);

            if (My_UI.Music_List_File.size() != 0) // 如果有音乐文件的话
            {
                My_UI.Music_List_Directory.clear();                         // 清除默认值{"/"}
                for (int i = 0; i < My_UI.Music_Scan_Directory.size(); i++) // 保存当前音乐文件路径
                {
                    if (My_UI.Music_Scan_Directory[i] == "/")
                    {
                        // 这里什么都不做，排除第一个是“/”的情况
                    }
                    else
                    {
                        My_UI.Music_List_Directory = My_UI.Music_List_Directory + "/" + My_UI.Music_Scan_Directory[i];
                    }
                }
                My_UI.Music_List_Total_Number = My_UI.Music_List_File.size();

                My_UI.Music_Scan_Prompt_Flag = My_UI.Music_Scan_Prompt_Success;
            }
            else // 如果找不到音乐文件的话
            {
                My_UI.Music_Scan_Prompt_Flag = My_UI.Music_Scan_Prompt_Fail;
            }

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_file_scanning_del == true)
                {
                    setup_scr_Music_file_scanning(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_file_scanning_del = true;
            }

            My_UI.Music_Scan_Prompt_Flag = My_UI.Music_Scan_Prompt_Normal; // 还原正常模式
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
static void Music_file_scanning_imgbtn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        for (int i; i < 3; i++) // 循环扫描三次SD卡
        {
            if (SD_Initialization() == true)
            {
                break;
            }
            else
            {
            }
        }

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.Music_file_scanning_del == true)
            {
                setup_scr_Music_file_scanning(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.Music_file_scanning_del = true;
        }

        break;
    }
    default:
        break;
    }
}

static void Music_file_scanning_msgbox_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_file_scanning_del == true)
                {
                    setup_scr_Music_file_scanning(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_file_scanning_del = true;
            }

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Music_file_scanning_msgbox_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Music_file_scanning_del == true)
                {
                    setup_scr_Music_file_scanning(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Music_file_scanning, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Music_file_scanning_del = true;
            }

            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Music_file_scanning(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Music_file_scanning, Music_file_scanning_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Music_file_scanning_list_1_item0, Music_file_scanning_list_1_item0_event_handler, LV_EVENT_ALL, NULL);

    if (My_UI.SD_Initialization_Flag == true)
    {
        lv_obj_add_event_cb(ui->Music_file_scanning_btnm_1, Music_file_scanning_btnm_1_event_handler, LV_EVENT_ALL, NULL);

        for (int i = 0; i < My_UI.AE_LV_List_Folder.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.AE_LV_List_Folder[i], Music_file_scanning_list_1_folder_event_handler, LV_EVENT_ALL, (void *)i);
        }

        if (My_UI.Music_Scan_Prompt_Flag == My_UI.Music_Scan_Prompt_Success)
        {
            lv_obj_add_event_cb(ui->Music_file_scanning_msgbox_1, Music_file_scanning_msgbox_1_event_handler, LV_EVENT_ALL, NULL);
        }
        if (My_UI.Music_Scan_Prompt_Flag == My_UI.Music_Scan_Prompt_Fail)
        {
            lv_obj_add_event_cb(ui->Music_file_scanning_msgbox_2, Music_file_scanning_msgbox_2_event_handler, LV_EVENT_ALL, NULL);
        }
    }

    if (My_UI.SD_Initialization_Flag == false)
    {
        lv_obj_add_event_cb(ui->Music_file_scanning_imgbtn_1, Music_file_scanning_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
    }
}
static void Battery_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Settings_del == true)
                {
                    setup_scr_Settings(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Settings_del = true;
            }

            My_UI.Battery_Information_Refresh_Flag = false; // 退出电池设置模式，关闭电池数据扫描

            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Settings_del == true)
                {
                    setup_scr_Settings(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Settings_del = true;
            }

            My_UI.Battery_Information_Refresh_Flag = false; // 退出电池设置模式，关闭电池数据扫描

            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Battery_ta_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_DEFOCUSED:
    {
        uint16_t temp = atoi(lv_textarea_get_text(guider_ui.Battery_ta_1));

        if (temp >= 3840 && temp <= 4608)
        {
            temp = ((temp - 3840) / 16); // 提取16的倍数
            My_UI.Battery_Control_Charge_Voltage_Limit = (temp * 16) + 3840;

            lv_textarea_set_text(guider_ui.Battery_ta_1, ((String)My_UI.Battery_Control_Charge_Voltage_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);

            // SY6970写入数据
            PMU.setChargeTargetVoltage(My_UI.Battery_Control_Charge_Voltage_Limit);
        }
        else
        {
            lv_textarea_set_text(guider_ui.Battery_ta_1, ((String)My_UI.Battery_Control_Charge_Voltage_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);
        }

        break;
    }
    default:
        break;
    }
}

static void Battery_ta_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_DEFOCUSED:
    {
        uint16_t temp = atoi(lv_textarea_get_text(guider_ui.Battery_ta_2));

        if (temp >= 0 && temp <= 5056)
        {
            temp = ((temp - 0) / 64); // 提取64的倍数
            My_UI.Battery_Control_Fast_Charge_Current_Limit = (temp * 64) + 0;

            lv_textarea_set_text(guider_ui.Battery_ta_2, ((String)My_UI.Battery_Control_Fast_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);

            // SY6970写入数据
            PMU.setChargerConstantCurr(My_UI.Battery_Control_Fast_Charge_Current_Limit);
        }
        else
        {
            lv_textarea_set_text(guider_ui.Battery_ta_2, ((String)My_UI.Battery_Control_Fast_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);
        }

        break;
    }
    default:
        break;
    }
}
static void Battery_ta_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_DEFOCUSED:
    {
        uint16_t temp = atoi(lv_textarea_get_text(guider_ui.Battery_ta_3));

        if (temp >= 64 && temp <= 1024)
        {
            temp = ((temp - 64) / 64); // 提取64的倍数
            My_UI.Battery_Control_Precharge_Charge_Current_Limit = (temp * 64) + 64;

            lv_textarea_set_text(guider_ui.Battery_ta_3, ((String)My_UI.Battery_Control_Precharge_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);

            // SY6970写入数据
            PMU.setPrechargeCurr(My_UI.Battery_Control_Precharge_Charge_Current_Limit);
        }
        else
        {
            lv_textarea_set_text(guider_ui.Battery_ta_3, ((String)My_UI.Battery_Control_Precharge_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);
        }
        break;
    }
    default:
        break;
    }
}
static void Battery_ta_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_DEFOCUSED:
    {
        uint16_t temp = atoi(lv_textarea_get_text(guider_ui.Battery_ta_4));

        if (temp >= 64 && temp <= 1024)
        {
            temp = ((temp - 64) / 64); // 提取64的倍数
            My_UI.Battery_Control_Termination_Charge_Current_Limit = (temp * 64) + 64;

            lv_textarea_set_text(guider_ui.Battery_ta_4, ((String)My_UI.Battery_Control_Termination_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);

            // SY6970写入数据
            PMU.setTerchargeCurr(My_UI.Battery_Control_Termination_Charge_Current_Limit);
        }
        else
        {
            lv_textarea_set_text(guider_ui.Battery_ta_4, ((String)My_UI.Battery_Control_Termination_Charge_Current_Limit).c_str());

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery);
        }
        break;
    }
    default:
        break;
    }
}

static void Battery_sw_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.SY6970_Initialization_Flag == true)
        {
            My_UI.Battery_Control_OTG_Mode_Flag = !My_UI.Battery_Control_OTG_Mode_Flag;

            if (My_UI.Battery_Control_OTG_Mode_Flag == My_UI.Battery_Control_OTG_ON)
            {
                if (PMU.enableOTG() == false)
                {
                    My_UI.Battery_Control_OTG_Mode_Flag = My_UI.Battery_Control_OTG_OFF;
                }
            }

            if (My_UI.Battery_Control_OTG_Mode_Flag == My_UI.Battery_Control_OTG_OFF)
            {
                PMU.disableOTG();
            }
        }

        break;
    }
    default:
        break;
    }
}
static void Battery_msgbox_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Settings_del == true)
                {
                    setup_scr_Settings(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Settings_del = true;
            }

            My_UI.Battery_Information_Refresh_Flag = false; // 退出电池设置模式，关闭电池数据扫描
            break;
        }
        case 1:
        {
            for (int i; i < 3; i++) // 循环扫描三次SY6970设备
            {
                if (SY6970_Initialization() == true)
                {
                    My_UI.Battery_Information_Refresh_Flag = true;
                    break;
                }
                else
                {
                    My_UI.Battery_Information_Refresh_Flag = false;
                }
            }

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Battery_del == true)
                {
                    setup_scr_Battery(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Battery, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Battery_del = true;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Battery(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Battery, Battery_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Battery_ta_1, Battery_ta_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Battery_ta_2, Battery_ta_2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Battery_ta_3, Battery_ta_3_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Battery_ta_4, Battery_ta_4_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Battery_sw_1, Battery_sw_1_event_handler, LV_EVENT_ALL, NULL);

    if (My_UI.SY6970_Initialization_Flag == false)
    {
        lv_obj_add_event_cb(ui->Battery_msgbox_1, Battery_msgbox_1_event_handler, LV_EVENT_ALL, NULL);
    }
}
static void WIFI_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Settings_del == true)
                {
                    setup_scr_Settings(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Settings_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Settings_del == true)
                {
                    setup_scr_Settings(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Settings, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Settings_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void WIFI_sw_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        My_UI.WiFi_Switch_Status = !My_UI.WiFi_Switch_Status;

        if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_ON)
        {
            WIFI_Device_ON();

            if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
            {
                My_UI.WIFI_Manager_C.clear();
                WIFI_Device_Scan(&My_UI.WIFI_Manager_C);
            }
        }

        if (My_UI.WiFi_Switch_Status == My_UI.WiFi_Switch_Status_OFF)
        {
            WIFI_Device_OFF();

            My_UI.WIFI_Manager_C.clear();
        }

        // Write the load screen code.
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
        {
            if (guider_ui.WIFI_del == true)
            {
                setup_scr_WIFI(&guider_ui);
            }
            lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
            guider_ui.WIFI_del = true;
        }

        break;
    }
    default:
        break;
    }
}
static void WIFI_list_1_judgment_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
        {

            My_UI.WIFI_Current_Number = (uint32_t)(e->user_data);

            if (My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_EncryptionType == 1)
            {
                My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Judgment_Encrypted; // 加密的WIFI
                // Serial.println("Encrypted");
            }
            else
            {
                My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Judgment_Unencrypted; // 未加密的WIFI
                // Serial.println("Unencrypted");
            }

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.WIFI_del == true)
                {
                    setup_scr_WIFI(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.WIFI_del = true;
            }
        }

        My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Normal; // 还原正常模式

        break;
    }
    default:
        break;
    }
}

static void WIFI_msgbox_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.WIFI_del == true)
                {
                    setup_scr_WIFI(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.WIFI_del = true;
            }

            break;
        }
        case 1:
        {
            String temp = lv_textarea_get_text(guider_ui.WIFI_ta_1); // 获取输入的WIFI密码

            if (WIFI_Connection_Encryption(My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name, temp) == true)
            {
                My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Connect_Successfully;
            }
            else
            {
                My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Connect_Fail;
            }

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.WIFI_del == true)
                {
                    setup_scr_WIFI(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.WIFI_del = true;
            }

            My_UI.WIFI_Prompt_Flag = My_UI.WIFI_Prompt_Normal;
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void WIFI_msgbox_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.WIFI_del == true)
                {
                    setup_scr_WIFI(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.WIFI_del = true;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
static void WIFI_msgbox_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_current_target(e);
        uint16_t id = lv_msgbox_get_active_btn(obj);
        switch (id)
        {
        case 0:
        {
            My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name = "[Connecting]: " +
                                                                        My_UI.WIFI_Manager_C[My_UI.WIFI_Current_Number].WIFI_Name;

            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.WIFI_del == true)
                {
                    setup_scr_WIFI(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.WIFI, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.WIFI_del = true;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_WIFI(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->WIFI, WIFI_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->WIFI_sw_1, WIFI_sw_1_event_handler, LV_EVENT_ALL, NULL);

    if (My_UI.WIFI_Device_Status == My_UI.WIFI_Device_Status_ON)
    {
        for (int16_t i = 0; i < My_UI.WIFI_LV_List_Name.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.WIFI_LV_List_Name[i], WIFI_list_1_judgment_event_handler, LV_EVENT_ALL, (void *)i);
        }

        if (My_UI.WIFI_Prompt_Flag == My_UI.WIFI_Prompt_Judgment_Encrypted)
        {
            lv_obj_add_event_cb(ui->WIFI_msgbox_1, WIFI_msgbox_1_event_handler, LV_EVENT_ALL, NULL);
        }
        if (My_UI.WIFI_Prompt_Flag == My_UI.WIFI_Prompt_Connect_Fail)
        {
            lv_obj_add_event_cb(ui->WIFI_msgbox_2, WIFI_msgbox_2_event_handler, LV_EVENT_ALL, NULL);
        }
        if (My_UI.WIFI_Prompt_Flag == My_UI.WIFI_Prompt_Connect_Successfully)
        {
            lv_obj_add_event_cb(ui->WIFI_msgbox_3, WIFI_msgbox_3_event_handler, LV_EVENT_ALL, NULL);
        }
    }
}
static void Camera_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Home_del == true)
                {
                    setup_scr_Home(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Home_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
static void Camera_btnm_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t *obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        lv_obj_t *act_scr = lv_scr_act();
        lv_disp_t *d = lv_obj_get_disp(act_scr);
        switch (id)
        {
        case 0:
        {
            My_UI.Window_Camera_Wifi_Mode = My_UI.Camera_Wifi_Mode_STA;

            // 刷新屏幕
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_Wifi_del == true)
                {
                    setup_scr_Camera_Wifi(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera_Wifi, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Camera_Wifi_del = true;
            }
            break;
        }
        case 1:
        {
            My_UI.Window_Camera_Wifi_Mode = My_UI.Camera_Wifi_Mode_SoftAP;

            // 刷新屏幕
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_Wifi_del == true)
                {
                    setup_scr_Camera_Wifi(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera_Wifi, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Camera_Wifi_del = true;
            }
            break;
        }
        case 2:
        {
            // OV2640_Initialization(OV2640_Pixel_Format::PIXFORMAT_RGB565);

            // 刷新屏幕
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_Screen_del == true)
                {
                    setup_scr_Camera_Screen(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera_Screen, LV_SCR_LOAD_ANIM_NONE, 200, 300, true);
                guider_ui.Camera_Screen_del = true;
            }
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Camera(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Camera, Camera_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Camera_btnm_1, Camera_btnm_1_event_handler, LV_EVENT_ALL, NULL);
}
static void Camera_Screen_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_del == true)
                {
                    setup_scr_Camera(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Camera_del = true;
            }
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            // Write the load screen code.
            lv_obj_t *act_scr = lv_scr_act();
            lv_disp_t *d = lv_obj_get_disp(act_scr);
            if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr))
            {
                if (guider_ui.Camera_del == true)
                {
                    setup_scr_Camera(&guider_ui);
                }
                lv_scr_load_anim(guider_ui.Camera, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true);
                guider_ui.Camera_del = true;
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
}
void events_init_Camera_Screen(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Camera_Screen, Camera_Screen_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{
}
