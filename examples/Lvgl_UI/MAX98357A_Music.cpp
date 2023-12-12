/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-12 14:46:04
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-17 19:02:48
 * @License: GPL 3.0
 */
#include "Audio.h"
#include "pin_config.h"
#include "custom.h"
#include "MAX98357A_Music.h"

Audio audio;

void MAX98357A_Initialization(void)
{
    audio.setPinout(MAX98357A_BCLK, MAX98357A_LRCLK, MAX98357A_DOUT);
    audio.setVolume(My_UI.System_Volume); // 0...21,Volume setting
    audio.forceMono(true);                // change stereo to mono
    // audio.setBalance(-16);
}

void MAX98357A_Music_Play_Loop(void)
{
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Switch)
    {
        if (My_UI.Playing_Load_Anim_Delay_Flag == My_UI.Playing_Load_Anim_Delay_ON)
        {
            My_UI.Playing_Load_Anim_Target_Delay = millis() + 500; // 500ms等待动画加载完成
            My_UI.Playing_Load_Anim_Delay_Flag = My_UI.Playing_Load_Anim_Delay_OFF;
        }

        if (millis() > My_UI.Playing_Load_Anim_Target_Delay)
        {
            SD_Initialization();

            if (My_UI.SD_Initialization_Flag == true)
            {
                audio.connecttoSD((My_UI.Music_List_Directory +
                                   +"/" + My_UI.Music_List_File[My_UI.Music_List_Current_Number].file_name)
                                      .c_str());
                // Serial.printf("%d", audio.getAudioCurrentTime());
                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Playing;
            }

            if (My_UI.SD_Initialization_Flag == false)
            {
            }
            My_UI.Playing_Load_Anim_Target_Delay = 4294967295LL; // 还原初始值
        }
    }
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Playing)
    {
        audio.loop();
    }

    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Pause)
    {
    }
}

void MAX98357A_Music_Data_Refresh(void)
{
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Playing)
    {
        // getAudioCurrentTime()总是大于getAudioFileDuration()
        //  Serial.printf("%d\n", audio.getAudioFileDuration());//音乐文件的时间
        //  Serial.printf("%d\n", audio.getAudioCurrentTime());//音乐当前播放的时间单位：秒
        //  Serial.printf("%d\n", audio.getTotalPlayingTime());//总执行audio.loop();函数的时间

        // Serial.printf("\n");

        if (audio.getAudioFileDuration() != 0) // 当能够获取到音乐文件总时间时
        {
            lv_obj_t *act_scr = lv_scr_act();
            My_UI.Playing_Current_Music_File_Duration = audio.getAudioFileDuration();
            My_UI.Playing_Current_Music_Time = audio.getAudioCurrentTime();

            if (My_UI.Playing_Current_Music_Time >= My_UI.Playing_Current_Music_File_Duration)
            {
                My_UI.Playing_Current_Static = My_UI.Playing_Current_Static_Pause;

                My_UI.Playing_Current_Music_Time = 0;

                // 暂停状态
                lv_imgbtn_set_state(guider_ui.Playing_imgbtn_1, LV_IMGBTN_STATE_RELEASED);

                // Update current screen layout.
                lv_obj_update_layout(guider_ui.Playing); // 刷新屏幕
            }

            if (act_scr->user_data == "Playing") // 判断当前窗口是否为Playing窗口
            {
                // String Current_Music_Time_Minute = "00";
                // String Current_Music_Time_Second = "00";

                // Current_Music_Time_Minute = (My_UI.Playing_Current_Music_Time / 60) < 10
                //                                 ? (String)("0" + (String)(My_UI.Playing_Current_Music_Time / 60))
                //                                 : (String)(My_UI.Playing_Current_Music_Time / 60);

                // Current_Music_Time_Second = (My_UI.Playing_Current_Music_Time % 60) < 10
                //                                 ? (String)("0" + (String)(My_UI.Playing_Current_Music_Time % 60))
                //                                 : (String)(My_UI.Playing_Current_Music_Time % 60);

                lv_label_set_text_fmt(guider_ui.Playing_label_2, "%02d:%02d",
                                      My_UI.Playing_Current_Music_Time / 60,
                                      My_UI.Playing_Current_Music_Time % 60);

                lv_label_set_text_fmt(guider_ui.Playing_label_3, "%02d:%02d",
                                      My_UI.Playing_Current_Music_File_Duration / 60,
                                      My_UI.Playing_Current_Music_File_Duration % 60);

                lv_slider_set_range(guider_ui.Playing_slider_3, 0, My_UI.Playing_Current_Music_File_Duration);
                lv_slider_set_value(guider_ui.Playing_slider_3, My_UI.Playing_Current_Music_Time, lv_anim_enable_t::LV_ANIM_OFF);

                // Update current screen layout.
                lv_obj_update_layout(guider_ui.Playing); // 刷新屏幕
            }
        }
    }
    if (My_UI.Playing_Current_Static == My_UI.Playing_Current_Static_Pause)
    {
    }
}

// // optional
// void audio_info(const char *info)
// {
//     Serial.print("info        ");
//     Serial.println(info);
// }
// void audio_id3data(const char *info)
// { // id3 metadata
//     Serial.print("id3data     ");
//     Serial.println(info);
// }
// void audio_eof_mp3(const char *info)
// { // end of file
//     Serial.print("eof_mp3     ");
//     Serial.println(info);
// }
// void audio_showstation(const char *info)
// {
//     Serial.print("station     ");
//     Serial.println(info);
// }
// void audio_showstreamtitle(const char *info)
// {
//     Serial.print("streamtitle ");
//     Serial.println(info);
// }
// void audio_bitrate(const char *info)
// {
//     Serial.print("bitrate     ");
//     Serial.println(info);
// }
// void audio_commercial(const char *info)
// { // duration in sec
//     Serial.print("commercial  ");
//     Serial.println(info);
// }
// void audio_icyurl(const char *info)
// { // homepage
//     Serial.print("icyurl      ");
//     Serial.println(info);
// }
// void audio_lasthost(const char *info)
// { // stream URL played
//     Serial.print("lasthost    ");
//     Serial.println(info);
// }
