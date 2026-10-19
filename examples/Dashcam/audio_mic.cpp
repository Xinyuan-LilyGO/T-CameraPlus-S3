// =====================================================================
//  audio_mic.cpp  -  see audio_mic.h   (arduino-esp32 2.0.x, legacy I2S)
// =====================================================================
#include "audio_mic.h"
#include "board_pins.h"
#include "config.h"
#include <Arduino.h>
#include <driver/i2s.h>
#include <freertos/FreeRTOS.h>
#include <freertos/stream_buffer.h>

namespace audio {

static const i2s_port_t I2S_PORT = I2S_NUM_0;
static StreamBufferHandle_t s_sb = nullptr;
static TaskHandle_t s_task = nullptr;
static volatile bool s_running = false;

// ~0.5 s of 16 kHz/16-bit mono headroom
static const size_t SB_BYTES = 16000 * 2 / 2;

static void audioTask(void *) {
    const size_t WORDS = 256;                 // 32-bit words read per iteration
    int32_t  raw[WORDS];
    int16_t  pcm[WORDS];
    while (s_running) {
        size_t bytesRead = 0;
        esp_err_t e = i2s_read(I2S_PORT, raw, sizeof(raw), &bytesRead, pdMS_TO_TICKS(100));
        if (e != ESP_OK || bytesRead == 0) continue;
        size_t n = bytesRead / sizeof(int32_t);
        for (size_t i = 0; i < n; ++i) {
            int32_t v = raw[i] >> AUDIO_GAIN_SHIFT;     // sensitivity / gain
            if (v > 32767) v = 32767; else if (v < -32768) v = -32768;
            pcm[i] = (int16_t)v;
        }
        // Drop samples if the consumer is behind (better than blocking capture).
        xStreamBufferSend(s_sb, pcm, n * sizeof(int16_t), 0);
    }
    vTaskDelete(nullptr);
}

bool begin() {
    s_sb = xStreamBufferCreate(SB_BYTES, 1);
    if (!s_sb) { log_e("audio stream buffer alloc failed"); return false; }

    i2s_config_t cfg = {};
    cfg.mode                 = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX);
    cfg.sample_rate          = AUDIO_SAMPLE_RATE;
    cfg.bits_per_sample      = I2S_BITS_PER_SAMPLE_32BIT;   // mic is 24-bit in 32-bit slot
    cfg.channel_format       = AUDIO_I2S_CHANNEL;           // mono (one populated slot)
    cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    cfg.intr_alloc_flags     = ESP_INTR_FLAG_LEVEL1;
    cfg.dma_buf_count        = 6;
    cfg.dma_buf_len          = 256;
    cfg.use_apll             = false;
    cfg.tx_desc_auto_clear   = false;

    if (i2s_driver_install(I2S_PORT, &cfg, 0, nullptr) != ESP_OK) {
        log_e("i2s_driver_install failed");
        return false;
    }

    i2s_pin_config_t pins = {};
    pins.bck_io_num   = PIN_MIC_BCLK;
    pins.ws_io_num    = PIN_MIC_WS;
    pins.data_out_num = I2S_PIN_NO_CHANGE;
    pins.data_in_num  = PIN_MIC_DATA;
    if (i2s_set_pin(I2S_PORT, &pins) != ESP_OK) {
        log_e("i2s_set_pin failed");
        return false;
    }
    i2s_zero_dma_buffer(I2S_PORT);

    s_running = true;
    xTaskCreatePinnedToCore(audioTask, "mic", 4096, nullptr, 4, &s_task, 0);
    log_i("audio mic ready: %u Hz mono", (unsigned)AUDIO_SAMPLE_RATE);
    return true;
}

size_t read(uint8_t *dst, size_t maxBytes) {
    if (!s_sb) return 0;
    return xStreamBufferReceive(s_sb, dst, maxBytes, 0);
}

size_t available() {
    if (!s_sb) return 0;
    return SB_BYTES - xStreamBufferSpacesAvailable(s_sb);
}

void flush() {
    if (s_sb) xStreamBufferReset(s_sb);
}

uint32_t sampleRate() { return AUDIO_SAMPLE_RATE; }
uint16_t channels()   { return AUDIO_CHANNELS; }
uint16_t bits()       { return AUDIO_BITS; }

}  // namespace audio
