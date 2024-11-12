/*
 * @Description:
    LVGL Configuration file:
    Copy your_arduino_path/libraries/lvgl/lv_conf_template.h
    to your_arduino_path/libraries/lv_conf.h

    In lv_conf.h around line 15, enable config file:
    #if 1 // Set it to "1" to enable content

    Then find and set:
    #define LV_COLOR_DEPTH     16
    #define LV_TICK_CUSTOM     1

    For SPI/parallel 8 display set color swap can be faster, parallel 16/RGB screen don't swap!
    #define LV_COLOR_16_SWAP   1 // for SPI and parallel 8
    #define LV_COLOR_16_SWAP   0 // for parallel 16 and RGB

 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-09-22 11:59:37
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-23 16:18:21
 * @License: GPL 3.0
 */
#include <lvgl.h>
#include <Arduino_GFX_Library.h>
#include "cst816t.h"
#include "pin_config.h"
#include "gui_guider.h"
#include "events_init.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "custom.h"
#include "MAX98357A_Music.h"

static uint32_t screenWidth = 240;  // screenWidth
static uint32_t screenHeight = 240; // screenHeight

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

cst816t touchpad(TP_RST, TP_INT);

lv_ui guider_ui;
My_Lvgl_UI My_UI;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (touchpad.available())
    {
        if (touchpad.finger_num > 0)
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = touchpad.x;
            data->point.y = touchpad.y;

            // Serial.print("Data x ");
            // Serial.println(touchpad.x);

            // Serial.print("Data y ");
            // Serial.println(touchpad.y);
        }
        else
        {
            data->state = LV_INDEV_STATE_REL;
        }
    }
}

void Lvgl_Initialization(void)
{
    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();

    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 40, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    while (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        delay(1000);
    }

    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 40);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
}

void setup()
{
    Serial.begin(115200);

    pinMode(LCD_BL, OUTPUT);
    ledcAttachPin(LCD_BL, 1); // assign TFT_BL pin to channel 1
    ledcSetup(1, 20000, 8);   // 12 kHz PWM, 8-bit resolution
    ledcWrite(1, 255);        // brightness 0 - 255

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(PIN_SD_MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    SPI.begin(SCLK, MISO, MOSI, SD_CS); // SPI boots

    if (SD_Initialization() != true)
    {
        Serial.printf("SD card initialization failed !\n");
        delay(1000);
    }
    
    MAX98357A_Initialization();

    Wire.begin(TP_SDA, TP_SCL);
    touchpad.begin(&Wire, mode_motion);

    // Init Display
    if (!gfx->begin())
    {
        Serial.println("gfx->begin() failed!");
    }
    gfx->fillScreen(BLACK);

    Lvgl_Initialization();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);

    MAX98357A_Music_Loop();
}