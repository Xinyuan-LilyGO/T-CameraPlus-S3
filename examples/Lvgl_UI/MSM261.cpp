/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-19 13:57:54
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2025-04-03 17:13:34
 * @License: GPL 3.0
 */
#include "pin_config.h"
#include "custom.h"

// 44.1 KHz
#define MICROPHONE_RECORD_TIME 10    // 采样时间
#define MICROPHONE_SAMPLE_RATE 44100 // 采样速率
#define MICROPHONE_DATA_BIT 16       // 数据位数
// 一秒采集的字节数量 计算方式：采样速率x声道数量x数据位数/8 (可以通过修改该值来修正录音出现噪点的情况)
#define MICROPHONE_BYTERATE (((MICROPHONE_SAMPLE_RATE * MICROPHONE_NUM_CHANNEL * MICROPHONE_DATA_BIT) / 8) + 11550)
#define MICROPHONE_WAVE_DATA_SIZE (MICROPHONE_RECORD_TIME * MICROPHONE_BYTERATE) // 采样字节
#define MICROPHONE_NUM_COMMUNICATION_DATA 500                                    // 每次采集的数据量

#define MICROPHONE_NUM_CHANNEL 2                                                   // 声道数量
#define MICROPHONE_BLOCKALIGN ((MICROPHONE_NUM_CHANNEL * MICROPHONE_DATA_BIT) / 8) // 块对齐方式

#define MICROPHONE_HEADER_SIZE 44

#define MICROPHONE_FILE_NAME "/sound.wav"

static size_t MSM261_CycleTime = 0;

byte Wave_Header[MICROPHONE_HEADER_SIZE]; // WAVE文件的文件头
char Wave_CommunicationData[MICROPHONE_NUM_COMMUNICATION_DATA];

File file;
#ifdef T_CameraPlus_S3_V1_0_V1_1
std::shared_ptr<Arduino_IIS_DriveBus> IIS_Bus =
    std::make_shared<Arduino_HWIIS>(I2S_NUM_0, MSM261_BCLK, MSM261_WS, MSM261_DATA);
#elif defined T_CameraPlus_S3_V1_2
std::shared_ptr<Arduino_IIS_DriveBus> IIS_Bus =
    std::make_shared<Arduino_HWIIS>(I2S_NUM_0, -1, MP34DT05TR_LRCLK, MP34DT05TR_DATA);
#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif

std::unique_ptr<Arduino_IIS> IIS(new Arduino_MEMS(IIS_Bus));

void MSM261_Initialization(void)
{
#ifdef T_CameraPlus_S3_V1_0_V1_1
    if (IIS->begin(i2s_mode_t::I2S_MODE_MASTER, ad_iis_data_mode_t::AD_IIS_DATA_IN, i2s_channel_fmt_t::I2S_CHANNEL_FMT_RIGHT_LEFT,
                   MICROPHONE_DATA_BIT, MICROPHONE_SAMPLE_RATE) == false)
    {
        Serial.println("MSM261 initialization fail");
        My_UI.MSM261_Initialization_Flag = false;
    }
    else
    {
        Serial.println("MSM261 initialization successfully");
        My_UI.MSM261_Initialization_Flag = true;
    }

#elif defined T_CameraPlus_S3_V1_2

    pinMode(MP34DT05TR_MAX98357_EN, OUTPUT);
    digitalWrite(MP34DT05TR_MAX98357_EN, LOW);

    if (IIS->begin(i2s_mode_t::I2S_MODE_PDM, ad_iis_data_mode_t::AD_IIS_DATA_IN, i2s_channel_fmt_t::I2S_CHANNEL_FMT_RIGHT_LEFT,
                   MICROPHONE_DATA_BIT, MICROPHONE_SAMPLE_RATE) == false)
    {
        Serial.println("MP34DT05TR initialization fail");
        My_UI.MSM261_Initialization_Flag = false;
    }
    else
    {
        Serial.println("MP34DT05TR initialization successfully");
        My_UI.MSM261_Initialization_Flag = true;
    }

#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif
}

void MSM261_Loop(void)
{
    lv_obj_t *act_scr = lv_scr_act();

    if (act_scr->user_data == "Recorder")
    {
        if (My_UI.MSM261_Initialization_Flag == true)
        {
            // if (My_UI.MSM261_Recording_Flag == My_UI.MSM261_Recording_ON)
            // {
            // /*
            //  * @brief 构建WAVE文件的头
            //  * @param header 构建WAVE的文件
            //  * @param totalDataLen 需要写入的数据长度
            //  * @param longSampleRate 采样频率
            //  * @param channels 声道数量
            //  * @param byteRate 字节速率 计算方式：采样速率x声道数量x数据位数/8
            //  * @param blockAlign 块对齐方式 计算方式：声道数量x数据位数/8
            // void createWavHeader(byte* header, int totalDataLen, int longSampleRate, uint8_t channels, int byteRate, uint8_t blockAlign);*/
            // microphone.createWavHeader(Wave_Header, MICROPHONE_WAVE_DATA_SIZE,
            //                            MICROPHONE_SAMPLE_RATE, MICROPHONE_NUM_CHANNEL, MICROPHONE_BYTERATE, 4);

            // SD.remove(MICROPHONE_FILE_NAME);
            // // 打开文件，如果没有文件就创建文件
            // file = SD.open(MICROPHONE_FILE_NAME, FILE_WRITE);
            // if (!file)
            // {
            //     return;
            // }
            // // 将wave文件的头写入文件中
            // file.write(Wave_Header, MICROPHONE_HEADER_SIZE);
            // Serial.println("start");
            // for (int j = 0; j < MICROPHONE_WAVE_DATA_SIZE / MICROPHONE_NUM_COMMUNICATION_DATA; ++j)
            // {
            //     microphone.read(Wave_CommunicationData, MICROPHONE_NUM_COMMUNICATION_DATA);

            //     // 单声道数据处理，当使用单声道时需要处理另一个声道的数据
            //     // 防止对有效声道的干扰产生杂音，当使用两个麦克风组成双声道时可以屏蔽此步骤。
            //     for (uint32_t i = 0; i < (MICROPHONE_NUM_COMMUNICATION_DATA >> 2); i++)
            //     {
            //         // 合并到右声道
            //         Wave_CommunicationData[(i << 2)] = 0;
            //         Wave_CommunicationData[(i << 2) + 1] = 0;

            //         // 合并到左声道
            //         // Wave_CommunicationData[(i << 2) + 2] = 0;
            //         // Wave_CommunicationData[(i << 2) + 3] = 0;
            //     }
            //     file.write((uint8_t *)Wave_CommunicationData, MICROPHONE_NUM_COMMUNICATION_DATA);
            // }
            // file.close();
            // // Serial.println("finish");

            // lv_obj_t *Recorder_win_1_label = lv_label_create(lv_win_get_content(guider_ui.Recorder_win_1));

            // My_UI.MSM261_Recording_Text += "\n\nRecord completed in 10 seconds\n";

            // lv_label_set_text(Recorder_win_1_label, (My_UI.MSM261_Recording_Text).c_str());
            // // Update current screen layout.
            // lv_obj_update_layout(guider_ui.Recorder);

            // My_UI.MSM261_Recording_Flag = My_UI.MSM261_Recording_OFF;
            // }

            if (MSM261_CycleTime < millis())
            {
                char temp_iis_read_buff[200] = {0};
                String temp;

                IIS->IIS_Read_Data(temp_iis_read_buff, 100);

                // temp = "left data: " + (String)((int16_t)((int16_t)temp_iis_read_buff[0] | (int16_t)temp_iis_read_buff[1] << 8)) + "\n";
                temp += "right data: " + (String)((int16_t)((int16_t)temp_iis_read_buff[2] | (int16_t)temp_iis_read_buff[3] << 8)) + "\n";

                lv_label_set_text(guider_ui.Recorder_tabview_1_tab_1_label, temp.c_str());
                // Update current screen layout.
                lv_obj_update_layout(guider_ui.Recorder);

                MSM261_CycleTime = millis() + 100;
            }
        }
    }
}