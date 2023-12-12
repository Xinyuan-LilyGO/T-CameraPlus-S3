/*
 * @Description: CST816D.cpp
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-08-25 17:09:20
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-30 13:56:45
 * @License: GPL 3.0
 */
/*
 demo of P168H002-CTP display.
 */
#include "Arduino_GFX_Library.h"
#include <Wire.h>
#include "cst816t.h"
#include "pin_config.h"

bool TP_Flag = false;

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

cst816t touchpad(TP_RST);

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(TP_INT, INPUT_PULLUP);

    attachInterrupt(
        TP_INT,
        []
        {
            TP_Flag = true;
            Serial.println("get_int");
        },
        FALLING);

    Wire.begin(SY6970_SDA, SY6970_SCL);
    touchpad.begin(&Wire, mode_motion);

    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, 255); // brightness 0 - 255

    gfx->begin();
    gfx->fillScreen(WHITE);

    gfx->setTextColor(PINK);
    gfx->setCursor(240 / 3, 240 / 3);
    gfx->println(touchpad.version());
    delay(1000);
}

void loop()
{
    if (TP_Flag == true)
    {
        TP_Flag = false;
        if (touchpad.available())
        {
            Serial.println(touchpad.state());
            Serial.println(touchpad.gesture_id);
            uint8_t touch_static = touchpad.gesture_id;
            uint8_t touch_x = touchpad.x;
            uint8_t touch_y = touchpad.y;

            gfx->setCursor(touch_x, touch_y);
            gfx->fillScreen(WHITE);
            gfx->setTextColor(MAGENTA);
            switch (touch_static)
            {
            case GESTURE_NONE:
                gfx->print("NONE");
                break;
            case GESTURE_SWIPE_DOWN:
                gfx->print("SWIPE UP"); // cst816d
                // gfx->print("SWIPE DOWN"); // cst816t
                break;
            case GESTURE_SWIPE_UP:
                gfx->print("SWIPE DOWN"); // cst816d
                // gfx->print("SWIPE UP"); // cst816t
                break;
            case GESTURE_SWIPE_LEFT:
                gfx->print("SWIPE LEFT");
                break;
            case GESTURE_SWIPE_RIGHT:
                gfx->print("SWIPE RIGHT");
                break;
            case GESTURE_SINGLE_CLICK:
                gfx->print("SINGLE CLICK");
                break;
            case GESTURE_DOUBLE_CLICK:
                gfx->print("DOUBLE CLICK");
                break;
            case GESTURE_LONG_PRESS:
                gfx->print("LONG PRESS");
                break;
            default:
                gfx->print("?");
                break;
            }
        }
    }
}
