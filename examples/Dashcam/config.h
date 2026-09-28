// =====================================================================
//  config.h  -  Dashcam tunables (edit these to taste)
// =====================================================================
#pragma once

// ---- Recording / loop -----------------------------------------------
#define REC_SEGMENT_SECONDS     60      // length of each clip before rotating
#define REC_DIR                 "/dashcam"
#define REC_FILE_PREFIX         "CLIP_"
#define REC_FILE_EXT            ".avi"
// Keep recording as long as the card has at least this much free space.
// When below the threshold the oldest clip(s) are deleted (loop recording).
#define REC_MIN_FREE_MB         150

// Snapshot photos (touch tap / KEY2 press) go here.
#define PHOTO_DIR               "/photos"
#define PHOTO_FILE_PREFIX       "IMG_"

// ---- Camera ---------------------------------------------------------
// JPEG quality: lower = higher quality + bigger files. 10-12 = high, 14-16 = medium.
// quality 14 saves ~30% file size vs 12, cutting SD write time and boosting fps.
#define CAM_JPEG_QUALITY        14
#define CAM_FB_COUNT            3                  // extra buffer: camera fills while SD writes
#define CAM_XCLK_HZ             24000000           // OV2640 max stable clock

// OV2640: SVGA is the native output window (~25fps).
//         HD forces internal UXGA-capture + DSP downscale → hardware limit ~8fps.
// OV5640: HD (1280×720) → 30fps sensor capability, but ~15fps recording on ESP32-S3.
//         FHD (1920×1080) → ~13fps sensor + SD bottleneck.
// Both land at standard dashcam 720p resolution in the AVI file.
#define CAM_FRAMESIZE_OV2640    FRAMESIZE_SVGA     // 800×600
#define CAM_FRAMESIZE_OV5640    FRAMESIZE_HD       // 1280×720, ~15fps (ESP32-S3 limited)

// ---- Audio (I2S mic) ------------------------------------------------
#define AUDIO_ENABLE            1
#define AUDIO_SAMPLE_RATE       16000   // Hz
#define AUDIO_BITS              16      // stored bits per sample in the AVI
#define AUDIO_CHANNELS          1
// MSM261 outputs 24-bit data left-justified in a 32-bit slot.
// Set to I2S_CHANNEL_FMT_ONLY_LEFT or _ONLY_RIGHT to match the populated channel.
#define AUDIO_I2S_CHANNEL       I2S_CHANNEL_FMT_ONLY_LEFT
// extra right-shift applied to the 32-bit raw sample before truncating to 16-bit
#define AUDIO_GAIN_SHIFT        11

// ---- Display / preview ----------------------------------------------
#define PREVIEW_ENABLE          1
// Draw a live preview frame to the LCD every Nth captured frame
// (keeps the shared SPI bus mostly free for SD writes).
#define PREVIEW_EVERY_N_FRAMES  6    // LCD preview holds SPI bus; increase to free more time for SD

// ---- AVI index --------------------------------------------------------
// Max chunks (video + audio) indexed per clip. Index lives in PSRAM.
// 2 streams * ~20fps * 60s ~= 2400; round up.
#define AVI_MAX_INDEX_ENTRIES   6000

// ---- Behaviour ------------------------------------------------------
#define AUTO_START_RECORDING    1       // begin recording automatically at boot
