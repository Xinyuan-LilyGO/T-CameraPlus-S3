/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-16 11:22:51
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-22 15:03:22
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include "gui_guider.h"
#include "widgets_init.h"

__attribute__((unused)) void kb_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *kb = lv_event_get_target(e);
    if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

__attribute__((unused)) void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
#if LV_USE_KEYBOARD || LV_USE_ZH_KEYBOARD
    lv_obj_t *ta = lv_event_get_target(e);
#endif
    lv_obj_t *kb = (lv_obj_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED || code == LV_EVENT_CLICKED)
    {
#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_foreground(kb);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
    if (code == LV_EVENT_CANCEL || code == LV_EVENT_DEFOCUSED)
    {

#if LV_USE_ZH_KEYBOARD != 0
        lv_zh_keyboard_set_textarea(kb, ta);
#endif
#if LV_USE_KEYBOARD != 0
        lv_keyboard_set_textarea(kb, ta);
#endif
        lv_obj_move_background(kb);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

#if LV_USE_ANALOGCLOCK != 0
void clock_count(int *hour, int *min, int *sec)
{
    (*sec)++;
    if (*sec == 60)
    {
        *sec = 0;
        (*min)++;
    }
    if (*min == 60)
    {
        *min = 0;
        if (*hour < 12)
        {
            (*hour)++;
        }
        else
        {
            (*hour)++;
            *hour = *hour % 12;
        }
    }
}
#endif

extern int Window_StatusBar_digital_clock_1_hour_value;
extern int Window_StatusBar_digital_clock_1_min_value;
extern int Window_StatusBar_digital_clock_1_sec_value;

void Window_StatusBar_digital_clock_1_timer(lv_timer_t *timer)
{
    clock_count_24(&Window_StatusBar_digital_clock_1_hour_value,
                   &Window_StatusBar_digital_clock_1_min_value,
                   &Window_StatusBar_digital_clock_1_sec_value);
    if (lv_obj_is_valid(guider_ui.Window_StatusBar_digital_clock_1))
    {
        lv_dclock_set_text_fmt(guider_ui.Window_StatusBar_digital_clock_1,
                               "%02d:%02d:%02d", Window_StatusBar_digital_clock_1_hour_value,
                               Window_StatusBar_digital_clock_1_min_value,
                               Window_StatusBar_digital_clock_1_sec_value);
    }
}
