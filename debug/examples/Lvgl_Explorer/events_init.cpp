/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

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
    lv_obj_add_event_cb(ui->Home_btn_1, Home_btn_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_2, Home_btn_2_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_3, Home_btn_3_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_4, Home_btn_4_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui->Home_btn_6, Home_btn_6_event_handler, LV_EVENT_ALL, NULL);
}
static void Playing_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_obj_set_height(guider_ui.Playing_cont_2, 0);
        break;
    }
    case LV_EVENT_SCREEN_UNLOADED:
    {
        lv_obj_add_flag(guider_ui.Playing_cont_2, LV_OBJ_FLAG_HIDDEN);
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
            // Write animation: Playing_cont_2 scale in width
            lv_anim_t Playing_cont_2_anim_width;
            lv_anim_init(&Playing_cont_2_anim_width);
            lv_anim_set_var(&Playing_cont_2_anim_width, guider_ui.Playing_cont_2);
            lv_anim_set_time(&Playing_cont_2_anim_width, 500);
            lv_anim_set_delay(&Playing_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&Playing_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&Playing_cont_2_anim_width, lv_obj_get_width(guider_ui.Playing_cont_2), 240);
            lv_anim_set_path_cb(&Playing_cont_2_anim_width, &lv_anim_path_ease_out);
            Playing_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&Playing_cont_2_anim_width);
            // Write animation: Playing_cont_2 scale in height
            lv_anim_t Playing_cont_2_anim_height;
            lv_anim_init(&Playing_cont_2_anim_height);
            lv_anim_set_var(&Playing_cont_2_anim_height, guider_ui.Playing_cont_2);
            lv_anim_set_time(&Playing_cont_2_anim_height, 500);
            lv_anim_set_delay(&Playing_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&Playing_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&Playing_cont_2_anim_height, lv_obj_get_height(guider_ui.Playing_cont_2), 0);
            lv_anim_set_path_cb(&Playing_cont_2_anim_height, &lv_anim_path_ease_out);
            Playing_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&Playing_cont_2_anim_height);
            break;
        }
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            lv_obj_clear_flag(guider_ui.Playing_cont_2, LV_OBJ_FLAG_HIDDEN);
            // Write animation: Playing_cont_2 scale in width
            lv_anim_t Playing_cont_2_anim_width;
            lv_anim_init(&Playing_cont_2_anim_width);
            lv_anim_set_var(&Playing_cont_2_anim_width, guider_ui.Playing_cont_2);
            lv_anim_set_time(&Playing_cont_2_anim_width, 500);
            lv_anim_set_delay(&Playing_cont_2_anim_width, 0);
            lv_anim_set_exec_cb(&Playing_cont_2_anim_width, (lv_anim_exec_xcb_t)lv_obj_set_width);
            lv_anim_set_values(&Playing_cont_2_anim_width, lv_obj_get_width(guider_ui.Playing_cont_2), 240);
            lv_anim_set_path_cb(&Playing_cont_2_anim_width, &lv_anim_path_ease_in);
            Playing_cont_2_anim_width.repeat_cnt = 0;
            lv_anim_start(&Playing_cont_2_anim_width);
            // Write animation: Playing_cont_2 scale in height
            lv_anim_t Playing_cont_2_anim_height;
            lv_anim_init(&Playing_cont_2_anim_height);
            lv_anim_set_var(&Playing_cont_2_anim_height, guider_ui.Playing_cont_2);
            lv_anim_set_time(&Playing_cont_2_anim_height, 500);
            lv_anim_set_delay(&Playing_cont_2_anim_height, 0);
            lv_anim_set_exec_cb(&Playing_cont_2_anim_height, (lv_anim_exec_xcb_t)lv_obj_set_height);
            lv_anim_set_values(&Playing_cont_2_anim_height, lv_obj_get_height(guider_ui.Playing_cont_2), 180);
            lv_anim_set_path_cb(&Playing_cont_2_anim_height, &lv_anim_path_ease_in);
            Playing_cont_2_anim_height.repeat_cnt = 0;
            lv_anim_start(&Playing_cont_2_anim_height);
            break;
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
void events_init_My_Music(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->My_Music, My_Music_event_handler, LV_EVENT_ALL, NULL);
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
        // Serial.println(My_UI.AE_Folder_Name[(int)(e->user_data)]);

        My_UI.AE_Current_Directory.push_back(My_UI.AE_Folder_Name[(int)(e->user_data)]);

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
        // Serial.println(My_UI.AE_File_Manager_S[(int)(e->user_data)].file_name + "   " + My_UI.AE_File_Manager_S[(int)(e->user_data)].file_size+"Kb");
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
        for (int i; i < 3; i++)
        {
            if (SD_Initialization() == true)
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
                break;
            }
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

    if (My_UI.AE_SD_Mode_Flag == true)
    {
        for (int i = 0; i < My_UI.Explorer_list_1_folder.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.Explorer_list_1_folder[i], Explorer_list_1_folder_event_handler, LV_EVENT_ALL, (void *)i);
        }
        for (int i = 0; i < My_UI.Explorer_list_1_file.size(); i++)
        {
            lv_obj_add_event_cb(My_UI.Explorer_list_1_file[i], Explorer_list_1_file_event_handler, LV_EVENT_ALL, (void *)i);
        }
    }
    if (My_UI.AE_SD_Mode_Flag == false)
    {
        lv_obj_add_event_cb(ui->Explorer_imgbtn_1, Explorer_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
    }
}

void events_init(lv_ui *ui)
{
}
