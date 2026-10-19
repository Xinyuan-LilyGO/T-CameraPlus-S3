# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **dashcam firmware** for the LILYGO T-CameraPlus-S3 (V1.0/V1.1) — an ESP32-S3 board with a 240×240 ST7789 LCD, OV2640/OV5640 camera, I2S digital microphone, SY6970 PMU, CST816S touch, and microSD card. The firmware records loop AVI clips (Motion-JPEG + PCM audio) to SD and displays a live preview on the LCD.

## Build & Flash Commands

```bash
# Build
pio run

# Flash
pio run -t upload

# Serial monitor (115200 baud)
pio device monitor

# Build + flash in one step
pio run -t upload && pio device monitor
```

After every build, `merge_bin.py` (post-script) produces a single flashable binary at `firmware_out/T-CameraPlus-S3_Dashcam.bin` containing bootloader + partition table + app.

## Host-side Unit Test (AVI muxer only)

The AVI writer has a standalone host test that requires no hardware:

```bash
g++ -std=c++14 -I../../src test/host/test_avi.cpp src/avi_writer.cpp -o test_avi
./test_avi
```

No PlatformIO test runner is used — this is a raw compile-and-run test.

## Architecture

### Task layout (FreeRTOS)

| Task | Core | Priority | Responsibility |
|------|------|----------|----------------|
| `recordTask` | 1 | 5 | Camera capture, SD writes, AVI muxing |
| `uiTask` | 0 | 3 | LCD preview, touch, KEY1 button, PMU polling |
| mic task (internal) | 0 | — | I2S capture → FreeRTOS stream buffer |

`setup()` / `loop()` run on core 1; `loop()` does nothing (everything is in tasks).

### Module namespaces

Each peripheral is wrapped in a C++ namespace with a `.h`/`.cpp` pair in `src/`:

- `cam::` — camera init, OV2640/OV5640 auto-detection (`camera_setup.cpp`)
- `audio::` — I2S mic capture, 16-bit mono PCM stream buffer (`audio_mic.cpp`)
- `storage::` — SD mount, clip/photo path sequencing via NVS, loop-delete (`sd_storage.cpp`)
- `display::` — ST7789 JPEG decode + blit + status overlay (`display_ui.cpp`)
- `touch::` — CST816S I2C touch polling (`touch_cst816.cpp`)
- `power::` — SY6970 PMU battery/charging status (`power_sy6970.cpp`)
- `spibus::` — shared SPI mutex + RAII `Guard` (`spi_bus.cpp`)
- `recorder::` — ties all the above together: loop recording, segment rotation, snapshot, preview hand-off (`recorder.cpp`)

`AviWriter` (`avi_writer.cpp`) is pure C++ (no Arduino headers) and writes a standard RIFF/AVI container with an `idx1` index. It depends only on the abstract `AviSink` interface, enabling the host-side unit test.

### Shared SPI bus constraint

The LCD and microSD **share one SPI bus** (SCLK=36, MOSI=35, MISO=37). All SD and LCD operations must hold `spibus::lock()` — use `spibus::Guard` for RAII. The recorder task calls `spibus::lock()`/`unlock()` around every `addVideoFrame` / `addAudioChunk`. The display module locks internally on every draw call.

### Preview hand-off

The recorder task writes a JPEG copy into a PSRAM buffer (`s_preview`) every `PREVIEW_EVERY_N_FRAMES` frames and sets `s_previewReady`. The UI task polls `recorder::getPreview()`, which does a mutex-guarded `memcpy` into a second PSRAM buffer allocated in `uiTask`. This avoids any direct pointer sharing between tasks.

### Key tunables (`include/config.h`)

All recording and hardware parameters live in `config.h`: clip length, JPEG quality, audio gain, preview rate, SD free-space threshold, auto-start behavior. Edit there rather than in the source files.

### Board pin map (`include/board_pins.h`)

All GPIO assignments for V1.0/V1.1. **V1.2 differs** (LCD/SD/PMU pins changed) — check the board silk-screen and update this file if targeting V1.2.

### Partition layout (`partitions.csv`)

Single large `factory` app partition (6 MB). No OTA. Small `storage` FAT partition on flash (not used at runtime — video goes to SD). NVS stores the clip/photo sequence counter.

### Dependencies (PlatformIO registry)

- `espressif32 @ 6.5.0` (arduino-esp32 core 2.0.14, LILYGO-validated)
- `Adafruit GFX`, `Adafruit ST7735/ST7789`, `Adafruit BusIO` — LCD drawing
- `JPEGDEC` — JPEG decode for LCD preview
- `XPowersLib` — SY6970 PMU driver
- `esp32-camera`, `SD`, `FS`, `SPI`, `Wire` — bundled with arduino-esp32 core
