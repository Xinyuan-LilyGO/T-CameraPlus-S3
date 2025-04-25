/*
 * @Description:
            T-Display-S3-Pro-MVSRBoard DMIC series microphone testing program
        Send left and right channel signal data on the serial port (value range between 40000 and -40000)
 * @Author: LILYGO_L
 * @Date: 2023-12-20 16:24:06
 * @LastEditTime: 2025-04-02 17:52:26
 * @License: GPL 3.0
 */
#include "Arduino_DriveBus_Library.h"
#include "pin_config.h"

#define IIS_SAMPLE_RATE 44100 // 采样速率
#define IIS_DATA_BIT 16       // 数据位数

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

short IIS_Read_Buff[100];

void setup()
{
    Serial.begin(115200);

#ifdef T_CameraPlus_S3_V1_0_V1_1
    while (IIS->begin(i2s_mode_t::I2S_MODE_MASTER, ad_iis_data_mode_t::AD_IIS_DATA_IN, i2s_channel_fmt_t::I2S_CHANNEL_FMT_RIGHT_LEFT,
                      IIS_DATA_BIT, IIS_SAMPLE_RATE) == false)
    {
        Serial.println("MSM261 initialization fail");
        delay(2000);
    }
    Serial.println("MSM261 initialization successfully");
#elif defined T_CameraPlus_S3_V1_2

    pinMode(MP34DT05TR_MAX98357_EN, OUTPUT);
    digitalWrite(MP34DT05TR_MAX98357_EN, LOW);

    while (IIS->begin(i2s_mode_t::I2S_MODE_PDM, ad_iis_data_mode_t::AD_IIS_DATA_IN, i2s_channel_fmt_t::I2S_CHANNEL_FMT_RIGHT_LEFT,
                      IIS_DATA_BIT, IIS_SAMPLE_RATE) == false)
    {
        Serial.println("MP34DT05TR initialization fail");
        delay(2000);
    }
    Serial.println("MP34DT05TR initialization successfully");
#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif
}

void loop()
{
    if (IIS->IIS_Read_Data(IIS_Read_Buff, sizeof(IIS_Read_Buff)) == true)
    {
        // 输出左右声道数据
        Serial.printf("Left: %d\n", IIS_Read_Buff[0]);
        Serial.printf("Right: %d\n", IIS_Read_Buff[1]);

        // Arduino
        // Serial.println(IIS_Read_Buff[0]);
        // Serial.print(",");
        // Serial.print(IIS_Read_Buff[1]);

        // for (int i = 0; i < 25; i++)
        // {
        //     Serial.printf("debug[%d]: %d\n", i, IIS_Read_Buff[i]);
        // }
    }
    else
    {
        Serial.printf("Failed to read iis data");
    }

    delay(50);
}
