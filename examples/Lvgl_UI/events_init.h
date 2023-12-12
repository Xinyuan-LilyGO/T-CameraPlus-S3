/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-06 10:54:55
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 11:22:24
 * @License: GPL 3.0
 */

#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "gui_guider.h"

    void events_init(lv_ui *ui);

    void events_init_Home(lv_ui *ui);
    void events_init_Playing(lv_ui *ui);
    void events_init_My_Music(lv_ui *ui);
    void events_init_Settings(lv_ui *ui);
    void events_init_Camera_Wifi(lv_ui *ui);
    void events_init_Recorder(lv_ui *ui);
    void events_init_Explorer(lv_ui *ui);
    void events_init_Music_list(lv_ui *ui);
    void events_init_Music_file_scanning(lv_ui *ui);
    void events_init_Battery(lv_ui *ui);
    void events_init_WIFI(lv_ui *ui);
    void events_init_Camera(lv_ui *ui);
    void events_init_Camera_Screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
