// =====================================================================
//  audio_mic.h  -  I2S digital microphone capture (MSM261S4030H0R)
//
//  A background task reads the I2S mic, converts to 16-bit mono PCM and
//  pushes it into a FreeRTOS stream buffer. The recorder drains it with
//  read() and muxes the bytes into the AVI audio stream.
// =====================================================================
#pragma once
#include <stdint.h>
#include <stddef.h>

namespace audio {

bool     begin();                                   // install I2S + start task
size_t   read(uint8_t *dst, size_t maxBytes);       // drain PCM (non-blocking)
size_t   available();                               // bytes ready to read
void     flush();                                   // discard buffered audio

uint32_t sampleRate();
uint16_t channels();
uint16_t bits();

}  // namespace audio
