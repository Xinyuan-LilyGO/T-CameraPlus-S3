/*
 * @Description(CN):
 *      这是针对于T-CameraPlus-S3编写的简易UI
 *
 * @Description(EN):
 *      This is a simple UI designed for T-CameraPlus-S3.
 *
 * @Author: LILYGO_L
 * @Date: 2023-09-22 11:59:37
 * @LastEditTime: 2025-04-25 09:18:43
 * @License: GPL 3.0
 */
#include "lvgl.h"
#include "Arduino_GFX_Library.h"
#include "pin_config.h"
#include "gui_guider.h"
#include "events_init.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include "custom.h"
#include "MAX98357A_Music.h"
#include "SY6970.h"
#include "MSM261.h"
#include "material_16Bit.h"

#define SOFTWARE_NAME "Original_Test"

#define SOFTWARE_LASTEDITTIME "202504081446"

#ifdef T_CameraPlus_S3_V1_0_V1_1
#define BOARD_VERSION "V1.0-V1.1"
#elif defined T_CameraPlus_S3_V1_2
#define BOARD_VERSION "V1.2"
#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif

static uint64_t screenWidth = 240;  // screenWidth
static uint64_t screenHeight = 240; // screenHeight

static uint64_t MAX98357A_CycleTime1 = 0;
static uint64_t MAX98357A_CycleTime2 = 0;

static uint64_t SY6970_CycleTime1 = 0;
static uint64_t SY6970_CycleTime2 = 0;

static uint64_t OV2640_CycleTime1 = 0;

TaskHandle_t Audio_Task_Handle = NULL;

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

lv_ui guider_ui;
My_Lvgl_UI My_UI;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

void Arduino_IIC_Touch_Interrupt(void)
{
    CST816D->IIC_Interrupt_Flag = true;
}

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
    if (CST816D->IIC_Interrupt_Flag == true)
    {
        if ((uint32_t)CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_FINGER_NUMBER) > 0)
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = (uint32_t)CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_X);
            data->point.y = (uint32_t)CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_Y);

            // Serial.print("Data x ");
            // Serial.println((uint32_t)CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_X));

            // Serial.print("Data y ");
            // Serial.println((uint32_t)CST816D->IIC_Read_Device_Value(CST816D->Arduino_IIC_Touch::Value_Information::TOUCH_COORDINATE_Y));

            CST816D->IIC_Interrupt_Flag = false;
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}
void lvgl_initialization(void)
{
    lv_init();

    screenWidth = gfx->width();
    screenHeight = gfx->height();

    // 使用PSRAM分配内存
    lv_color_t *buf_1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * 1024, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    lv_color_t *buf_2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * LCD_WIDTH * 1024, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);

    while ((!buf_1) || (!buf_2))
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
        delay(1000);
    }

    lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, LCD_WIDTH * 1024);

    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.full_refresh = 1; // 双缓冲全像素刷新
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
    Serial.println("Ciallo");
    Serial.println("[T-CameraPlus-S3_" + (String)BOARD_VERSION "][" + (String)SOFTWARE_NAME +
                   "]_firmware_" + (String)SOFTWARE_LASTEDITTIME);

    // 摄像头必须第一个初始化
    OV2640_Initialization(OV2640_Pixel_Format::PIXFORMAT_JPEG);
    // OV2640_Initialization(OV2640_Pixel_Format::PIXFORMAT_RGB565); // 需要屏幕显示摄像头数据时取消注释这个

    AP1511_Initialization();

    pinMode(LCD_BL, OUTPUT);

    ledcAttachPin(LCD_BL, 1);
    ledcSetup(1, 20000, 8);
    ledcWrite(1, My_UI.System_Screen_Brightness); // brightness 0 - 255

    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    // pinMode(PIN_SD_MISO, INPUT_PULLUP);                         // MISO pull-up resistor
    SPI.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SD_CS); // SPI boots

// Init Display
#ifdef T_CameraPlus_S3_V1_0_V1_1
    if (!gfx->begin())
    {
        Serial.println("gfx->begin() failed!");
    }
#elif defined T_CameraPlus_S3_V1_2
    if (!gfx->begin(80000000))
    {
        Serial.println("gfx->begin() failed!");
    }
#else
#error "Unknown macro definition. Please select the correct macro definition."
#endif

    gfx->fillScreen(BLACK);
    gfx->draw16bitRGBBitmap(0, 0, (uint16_t *)gImage_1, 240, 240);

    for (uint16_t i = 0; i < 255; i++) // 打开屏幕
    {
        My_UI.System_Screen_Brightness++;
        ledcWrite(1, My_UI.System_Screen_Brightness);
        delay(2);
    }
    delay(1000);

    if (SD_Initialization() != true)
    {
        Serial.printf("SD card initialization failed !\n");
        delay(1000);
    }

    if (SY6970_Initialization() != true)
    {
        Serial.printf("SY6970 initialization failed !\n");
        delay(1000);
    }

    MAX98357A_Initialization();

    MSM261_Initialization();

    if (CST816D->begin() == false)
    {
        Serial.println("CST816D initialization fail");
    }
    else
    {
        Serial.println("CST816D initialization successfully");

        // 中断模式为检测到触摸时，发出低脉冲
        CST816D->IIC_Write_Device_State(CST816D->Arduino_IIC_Touch::Device::TOUCH_DEVICE_INTERRUPT_MODE,
                                        CST816D->Arduino_IIC_Touch::Device_Mode::TOUCH_DEVICE_INTERRUPT_PERIODIC);
    }

    lvgl_initialization();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
}

void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    // delay(5);

    if (micros() > MAX98357A_CycleTime1)
    {
        MAX98357A_Music_Play_Loop();
        MAX98357A_CycleTime1 = micros() + 10; // 10us
    }

    if (millis() > MAX98357A_CycleTime2)
    {
        MAX98357A_Music_Data_Refresh();
        MAX98357A_CycleTime2 = millis() + 1000; // 1000ms
    }

    if (millis() > SY6970_CycleTime1)
    {
        My_UI_Battery_Loop();
        SY6970_CycleTime1 = millis() + 1500; // 1500ms
    }

    if (millis() > SY6970_CycleTime2)
    {
        My_UI_Window_StatusBar_Charge_State_Refresh();
        SY6970_CycleTime2 = millis() + 2500; // 2500ms
    }

    AP1511_Loop();

    MSM261_Loop();

    if (millis() > OV2640_CycleTime1)
    {
        OV2640_Loop();
        OV2640_CycleTime1 = millis() + 1; // 1ms
    }
}