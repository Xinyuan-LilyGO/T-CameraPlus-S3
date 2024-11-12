/*
 * @Description: CST816D_2.cpp
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-11-25 09:12:55
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-12 11:28:56
 * @License: GPL 3.0
 */
#include "Arduino_GFX_Library.h"
#include "Arduino_DriveBus_Library.h"
#include "pin_config.h"

// fp-133h01d
Arduino_DataBus *bus = new Arduino_HWSPI(
    LCD_DC /* DC */, LCD_CS /* CS */, LCD_SCLK /* SCK */, LCD_MOSI /* MOSI */, -1 /* MISO */);

Arduino_GFX *gfx = new Arduino_ST7789(
    bus, LCD_RST /* RST */, 0 /* rotation */, true /* IPS */,
    LCD_WIDTH /* width */, LCD_HEIGHT /* height */,
    0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col_offset2 */, 0 /* row_offset2 */);

std::shared_ptr<Arduino_IIC_DriveBus> IIC_Bus =
    std::make_shared<Arduino_HWIIC>(IIC_SDA, IIC_SCL, &Wire);

void Arduino_IIC_Touch_Interrupt(void);

std::unique_ptr<Arduino_IIC> CST816D(new Arduino_CST816x(IIC_Bus, CST816D_DEVICE_ADDRESS,
                                                         TP_RST, TP_INT, Arduino_IIC_Touch_Interrupt));

void Arduino_IIC_Touch_Interrupt(void)
{
    CST816D->IIC_Interrupt_Flag = true;
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    pinMode(LCD_BL, OUTPUT);
    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, 255); // brightness 0 - 255

    while (CST816D->begin() == false)
    {
        Serial.println("CST816D initialization fail");
        delay(2000);
    }
    Serial.println("CST816D initialization successfully");

    gfx->begin();
    gfx->fillScreen(WHITE);

    gfx->setTextColor(PINK);
    gfx->setCursor(240 / 3, 240 / 3);
    gfx->printf("IIC device ID: %#X \n\n", (int32_t)CST816D->IIC_Read_Device_ID());

    gfx->setTextColor(MAGENTA);
    delay(1000);
}

void loop()
{
    if (CST816D->IIC_Interrupt_Flag == true)
    {
        CST816D->IIC_Interrupt_Flag = false;

        gfx->setCursor(50, 50);
        gfx->fillScreen(WHITE);

        gfx->printf("\nTouch Gesture: %s \n",
                    (CST816D->IIC_Read_Device_State(CST816D->Arduino_IIC_Touch::Status_Information::TOUCH_GESTURE_ID)).c_str());

        gfx->printf("\nNumber of touch fingers: %d \n",
                    CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_FINGER_NUMBER));
    }
}
