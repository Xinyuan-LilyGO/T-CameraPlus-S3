/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-07-10 19:41:08
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-07-24 17:04:57
 * @License: GPL 3.0
 */
// ESP32_C3_Air101_Expansion_LCD_80X160 Configuration
#define USER_SETUP_ID 303

#define ST7735_DRIVER

#define TFT_WIDTH 128
#define TFT_HEIGHT 128

// #define ST7735_INITB
// #define ST7735_GREENTAB
#define ST7735_GREENTAB2
// #define ST7735_GREENTAB3
// #define ST7735_GREENTAB128    // For 128 x 128 display
// #define ST7735_GREENTAB160x80 // For 160 x 80 display (BGR, inverted, 26 offset)
// #define ST7735_REDTAB
// #define ST7735_BLACKTAB
// #define ST7735_REDTAB160x80   // For 160 x 80 display with 24 pixel offset

// #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR // Colour order Blue-Green-Red

#define TFT_INVERSION_ON
// #define TFT_INVERSION_OFF

// ESP32_C3_Air101_Expansion_LCD_80X160 Pin configuration
#define TFT_MISO -1
#define TFT_MOSI 10
#define TFT_SCLK 11
#define TFT_CS 13 // 1
// #define TFT_CS 12 // 2
// #define TFT_CS 14 // 3
// #define TFT_CS 21 // 4
#define TFT_DC 9 // Data Command control pin
#define TFT_RST 46 // Reset pin (could connect to RST pin)
#define TFT_BL 3 // LED back-light

#define LOAD_GLCD  // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2 // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4 // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6 // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7 // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8 // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
// #define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

// #define SPI_FREQUENCY  20000000
// #define SPI_FREQUENCY 27000000
#define SPI_FREQUENCY 40000000

#define SPI_TOUCH_FREQUENCY 2500000

// #define SUPPORT_TRANSACTIONS
