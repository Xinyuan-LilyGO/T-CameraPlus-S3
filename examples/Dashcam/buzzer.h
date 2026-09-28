#pragma once
#include <stdint.h>
#include <stddef.h>

namespace buzzer {
    bool begin();
    // Square-wave beep through MAX98357A.  Blocks the caller for durationMs.
    void beep(uint32_t freqHz = 880, uint32_t durationMs = 80);
    // Play raw WAV data (PCM, 8 or 16-bit, mono or stereo).  Blocks until done.
    void playWav(const uint8_t* data, size_t len);
}
