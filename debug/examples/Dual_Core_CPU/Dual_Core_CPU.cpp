/*
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-09-22 18:30:19
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-22 18:35:54
 * @License: GPL 3.0
 */
#include <Arduino.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>

// wifi在core0，其他在core1；1为大核

void Task1(void *pvParameters)
{
    // 在这里可以添加一些代码，这样的话这个任务执行时会先执行一次这里的内容
    // 当然后面进入while循环之后不会再执行这部分了
    while (1)
    {
        vTaskDelay(1000);
        Serial.print("PRO_CPU正在运行：");
        Serial.println(xPortGetCoreID());
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(1000);
        Serial.print("APP_CPU正在运行：");
        Serial.println(xPortGetCoreID());
    }
}

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // 关闭低电压检测,避免无限重启

    // 实现任务的函数名称（task1）；
    //任务的任何名称（“ task1”等）；
    // 分配给任务的堆栈大小，以字为单位；
    //任务输入参数（可以为NULL）；
    // 任务的优先级（0是最低优先级）；
    //任务句柄（可以为NULL）；
    // 任务将运行的内核ID（0或1）
    // 最后一个参数至关重要，决定这个任务创建在哪个核上.
    // PRO_CPU 为 0, APP_CPU 为 1,或者 tskNO_AFFINITY 允许任务在两者上运行.
    xTaskCreatePinnedToCore(Task1, "Task1", 10000, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(Task2, "Task2", 10000, NULL, 1, NULL, 1);

    Serial.begin(115200);
}

void loop()
{
}