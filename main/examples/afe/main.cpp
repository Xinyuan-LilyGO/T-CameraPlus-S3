/*
 * @Description: Afe
 * @Author: LILYGO_L
 * @Date: 2025-07-22 15:02:53
 * @LastEditTime: 2025-07-23 16:03:24
 * @License: GPL 3.0
 */
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wn_iface.h"
#include "esp_wn_models.h"
#include "esp_afe_sr_models.h"
#include "esp_mn_iface.h"
#include "esp_mn_models.h"
#include "model_path.h"
#include "string.h"
#include "pin_config.h"
#include "cpp_bus_driver_library.h"
#include "hiesp.h"
#include "hilexin.h"

#define MCLK_MULTIPLE i2s_mclk_multiple_t::I2S_MCLK_MULTIPLE_256
#define SAMPLE_RATE 16000

esp_afe_sr_iface_t *afe_handle = NULL;

#ifdef T_CameraPlus_S3_V1_0_V1_1

auto IIS_Bus = std::make_shared<Cpp_Bus_Driver::Hardware_Iis>(MSM261_DATA, DEFAULT_CPP_BUS_DRIVER_VALUE,
                                                              MSM261_WS, MSM261_BCLK, DEFAULT_CPP_BUS_DRIVER_VALUE, i2s_port_t::I2S_NUM_0,
                                                              Cpp_Bus_Driver::Hardware_Iis::Data_Mode::INPUT, Cpp_Bus_Driver::Hardware_Iis::Iis_Mode::STD);

#elif defined T_CameraPlus_S3_V1_2

auto IIS_Bus = std::make_shared<Cpp_Bus_Driver::Hardware_Iis>(MP34DT05TR_DATA, DEFAULT_CPP_BUS_DRIVER_VALUE,
                                                              MP34DT05TR_LRCLK, DEFAULT_CPP_BUS_DRIVER_VALUE, DEFAULT_CPP_BUS_DRIVER_VALUE, i2s_port_t::I2S_NUM_0,
                                                              Cpp_Bus_Driver::Hardware_Iis::Data_Mode::INPUT, Cpp_Bus_Driver::Hardware_Iis::Iis_Mode::PDM);

#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif

auto Esp32s3 = std::make_unique<Cpp_Bus_Driver::Tool>();

void feed_Task(void *arg)
{
    esp_afe_sr_data_t *afe_data = arg;
    int audio_chunksize = afe_handle->get_feed_chunksize(afe_data);
    int nch = afe_handle->get_feed_channel_num(afe_data);

    auto iis_buffer = std::make_unique<int16_t[]>(audio_chunksize * sizeof(int16_t));

    while (1)
    {
        IIS_Bus->read(iis_buffer.get(), audio_chunksize * sizeof(uint16_t));

        // IIS_Bus->write(iis_buffer, audio_chunksize * sizeof(uint16_t) * 2);

        // for (uint8_t i = 0; i < 10; i++)
        // {
        //     printf("read_data: %d\n", iis_buffer[i]);
        // }

        // 音量放大20倍（限制在 int16_t 范围内防止溢出）
        int16_t *ptr = iis_buffer.get();
        for (int i = 0; i < sizeof(audio_chunksize * 2); i++)
        {
            int32_t amplified = *ptr * 20;
            *ptr++ = (amplified > 32767) ? 32767 : (amplified < -32768) ? -32768
                                                                        : amplified;
        }

        afe_handle->feed(afe_data, iis_buffer.get());

        vTaskDelay(pdMS_TO_TICKS(50));
    }

    vTaskDelete(NULL);
}

void detect_Task(void *arg)
{
    esp_afe_sr_data_t *afe_data = arg;
    int afe_chunksize = afe_handle->get_fetch_chunksize(afe_data);
    printf("------------detect start------------\n");

    // modify wakenet detection threshold
    afe_handle->set_wakenet_threshold(afe_data, 1, 0.4); // set model1's threshold to 0.6
    afe_handle->set_wakenet_threshold(afe_data, 2, 0.4); // set model2's threshold to 0.6
    // afe_handle->reset_wakenet_threshold(afe_data, 1); // reset model1's threshold to default
    // afe_handle->reset_wakenet_threshold(afe_data, 2); // reset model2's threshold to default

    size_t cycle_time = 0;
    while (1)
    {
        afe_fetch_result_t *res = afe_handle->fetch(afe_data);
        if (!res || res->ret_value == ESP_FAIL)
        {
            printf("fetch error!\n");
            break;
        }

        if (esp_log_timestamp() > cycle_time)
        {
            // 这里检测是否有语音
            printf("vad state: %d\n", res->vad_state);
            cycle_time = esp_log_timestamp() + 1000;
        }

        if (res->wakeup_state == WAKENET_DETECTED)
        {
            printf("wakeword detected\n");
            printf("model index:%d, word index:%d\n", res->wakenet_model_index, res->wake_word_index);
            printf("-----------LISTENING-----------\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    vTaskDelete(NULL);
}

void Afe_Init()
{
    srmodel_list_t *models = esp_srmodel_init("model");
    if (models)
    {
        for (int i = 0; i < models->num; i++)
        {
            if (strstr(models->model_name[i], ESP_WN_PREFIX) != NULL)
            {
                printf("wakenet model in flash: %s\n", models->model_name[i]);
            }
        }
    }

    afe_config_t *afe_config = afe_config_init("NM", models, AFE_TYPE_SR, AFE_MODE_LOW_COST);

    // print/modify wake word model.
    if (afe_config->wakenet_model_name)
    {
        printf("wakeword model in AFE config: %s\n", afe_config->wakenet_model_name);
    }
    if (afe_config->wakenet_model_name_2)
    {
        printf("wakeword model in AFE config: %s\n", afe_config->wakenet_model_name_2);
    }

    afe_handle = esp_afe_handle_from_config(afe_config);
    esp_afe_sr_data_t *afe_data = afe_handle->create_from_config(afe_config);

    //
    afe_config_free(afe_config);

    xTaskCreatePinnedToCore(&feed_Task, "feed", 8 * 1024, (void *)afe_data, 5, NULL, 0);
    xTaskCreatePinnedToCore(&detect_Task, "detect", 4 * 1024, (void *)afe_data, 5, NULL, 1);
}

void Wakenet_Init()
{
    srmodel_list_t *models = esp_srmodel_init("model");
    char *model_name = esp_srmodel_filter(models, ESP_WN_PREFIX, "hilexin");
    esp_wn_iface_t *wakenet = (esp_wn_iface_t *)esp_wn_handle_from_name(model_name);
    model_iface_data_t *model_data = wakenet->create(model_name, DET_MODE_95);

    int audio_chunksize = wakenet->get_samp_chunksize(model_data) * sizeof(int16_t);
    int16_t *buffer = (int16_t *)malloc(audio_chunksize);
    unsigned char *data = NULL;
    size_t data_size = 0;
    if (strstr(model_name, "hiesp") != NULL)
    {
        data = (unsigned char *)hiesp;
        data_size = sizeof(hiesp);
        printf("wake word: %s, size:%d\n", "hiesp", data_size);
    }
    else if (strstr(model_name, "hilexin") != NULL)
    {
        data = (unsigned char *)hilexin;
        data_size = sizeof(hilexin);
        printf("wake word: %s, size:%d\n", "hilexin", data_size);
    }

    int chunks = 0;
    while (1)
    {
        if ((chunks + 1) * audio_chunksize <= data_size)
        {
            memcpy(buffer, data + chunks * audio_chunksize, audio_chunksize);
        }
        else
        {
            chunks = 0;
            // break;
        }

        wakenet_state_t state = wakenet->detect(model_data, buffer);
        if (state == WAKENET_DETECTED)
        {
            printf("Detected\n");
        }
        chunks++;

        vTaskDelay(pdMS_TO_TICKS(10));
    }

    wakenet->destroy(model_data);
    vTaskDelete(NULL);
}

extern "C" void app_main()
{
    printf("Ciallo\n");

#ifdef T_CameraPlus_S3_V1_0_V1_1

#elif defined T_CameraPlus_S3_V1_2

    Esp32s3->pin_mode(MP34DT05TR_MAX98357_EN, Cpp_Bus_Driver::Tool::Pin_Mode::OUTPUT);
    Esp32s3->pin_write(MP34DT05TR_MAX98357_EN, 0);

#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif

    IIS_Bus->begin(MCLK_MULTIPLE, SAMPLE_RATE, i2s_data_bit_width_t::I2S_DATA_BIT_WIDTH_16BIT);

    // Wakenet_Init();
    Afe_Init();
}
