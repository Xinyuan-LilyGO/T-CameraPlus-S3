// =====================================================================
//  board_pins.h  -  LILYGO T-CameraPlus-S3  V1.2 pin map
//
//  Source: official LILYGO pin_config.h (T_CameraPlus_S3_V1_2 variant).
//  V1.0 / V1.1 differences: SPI SCLK/MOSI/MISO, LCD_CS, LCD_RST,
//  I2C SDA/SCL, touch RST, camera PWDN/RESET/VSYNC, and mic wiring.
// =====================================================================
#pragma once

// ---------------------------------------------------------------------
//  Shared SPI bus  (LCD + microSD share SCLK & MOSI, separate CS lines)
// ---------------------------------------------------------------------
#define PIN_SPI_SCLK     35
#define PIN_SPI_MOSI     34
#define PIN_SPI_MISO     48     // used by the SD card

// ---- ST7789V LCD (240x240) ----
#define PIN_LCD_CS       36
#define PIN_LCD_DC       45
#define PIN_LCD_RST      -1     // no RST pin on V1.2
#define PIN_LCD_BL       46     // backlight (active HIGH)
#define LCD_WIDTH        240
#define LCD_HEIGHT       240

// ---- microSD (SPI mode) ----
#define PIN_SD_CS        21

// ---------------------------------------------------------------------
//  Shared I2C bus  (CST816S touch + SY6970 PMU)
//  NOTE: camera SCCB uses its own dedicated pins (1/2), not this bus.
// ---------------------------------------------------------------------
#define PIN_I2C_SDA      33
#define PIN_I2C_SCL      37

#define TOUCH_ADDR_CST816 0x15
#define PIN_TOUCH_RST    -1     // no touch RST pin on V1.2
#define PIN_TOUCH_INT    47     // we poll instead of using the interrupt

#define PMU_ADDR_SY6970   0x6A

// ---------------------------------------------------------------------
//  Camera (DVP parallel)  -  OV2640
// ---------------------------------------------------------------------
#define CAM_PIN_PWDN      4
#define CAM_PIN_RESET    -1
#define CAM_PIN_XCLK      7
#define CAM_PIN_SIOD      1     // camera SCCB SDA (not shared with I2C bus)
#define CAM_PIN_SIOC      2     // camera SCCB SCL (not shared with I2C bus)
#define CAM_PIN_D7        6
#define CAM_PIN_D6        8
#define CAM_PIN_D5        9
#define CAM_PIN_D4       11
#define CAM_PIN_D3       13
#define CAM_PIN_D2       15
#define CAM_PIN_D1       14
#define CAM_PIN_D0       12
#define CAM_PIN_VSYNC     3
#define CAM_PIN_HREF      5
#define CAM_PIN_PCLK     10

// AP1511B IR-cut filter switch (color/IR). Drive depending on day/night.
#define PIN_IRCUT_FBC    16

// ---------------------------------------------------------------------
//  Digital microphone (MP34DT05TR - PDM mode via I2S peripheral)
//  V1.2 replaces MSM261 with MP34DT05TR; LRCLK/DATA only (no BCLK).
//  MAX98357A enable shared on pin 18.
// ---------------------------------------------------------------------
#define PIN_MIC_BCLK     -1    // PDM: no bit clock
#define PIN_MIC_WS       40    // MP34DT05TR LRCLK
#define PIN_MIC_DATA     38    // MP34DT05TR DATA
#define PIN_MIC_AMP_EN   18    // MP34DT05TR / MAX98357A shared enable

// ---------------------------------------------------------------------
//  I2S amplifier  (MAX98357A)  -  not used by the dashcam, defined for ref
// ---------------------------------------------------------------------
#define PIN_AMP_BCLK     41
#define PIN_AMP_LRCLK    42
#define PIN_AMP_DATA     39

// ---------------------------------------------------------------------
//  Buttons  (active LOW, internal pull-up)
// ---------------------------------------------------------------------
#define PIN_KEY1         17     // snapshot → saved to PHOTO_DIR
#define PIN_KEY2          0     // toggle recording start / stop

