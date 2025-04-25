/*
 * @Description: None
 * @Author: LILYGO_L
 * @Date: 2025-04-03 14:11:27
 * @LastEditTime: 2025-04-03 14:11:41
 * @License: GPL 3.0
 */
#include "Arduino_DriveBus_Library.h"
#include "pin_config.h"

std::shared_ptr<Arduino_IIC_DriveBus> IIC_Bus =
    std::make_shared<Arduino_HWIIC>(IIC_SDA, IIC_SCL, &Wire);

std::unique_ptr<Arduino_IIC> SY6970(new Arduino_SY6970(IIC_Bus, SY6970_DEVICE_ADDRESS,
                                                       DRIVEBUS_DEFAULT_VALUE, DRIVEBUS_DEFAULT_VALUE));

static bool Temp1 = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println("Ciallo");

    while (SY6970->begin() == false)
    {
        Serial.println("SY6970 initialization fail");
        delay(2000);
    }
    Serial.println("SY6970 initialization successfully");

    // 开启ADC测量功能
    while (SY6970->IIC_Write_Device_State(SY6970->Arduino_IIC_Power::Device::POWER_DEVICE_ADC_MEASURE,
                                          SY6970->Arduino_IIC_Power::Device_State::POWER_DEVICE_ON) == false)
    {
        Serial.println("SY6970 ADC Measure ON fail");
        delay(2000);
    }
    Serial.println("SY6970 ADC Measure ON successfully");

    // 禁用看门狗定时器喂狗功能
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_WATCHDOG_TIMER, 0);
    // 热调节阈值设置为60度
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_THERMAL_REGULATION_THRESHOLD, 60);
    // 充电目标电压电压设置为4224mV
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_CHARGING_TARGET_VOLTAGE_LIMIT, 4224);
    // 最小系统电压限制为3600mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_MINIMUM_SYSTEM_VOLTAGE_LIMIT, 3600);
    // 设置OTG电压为5062mV
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_OTG_VOLTAGE_LIMIT, 5062);
    // 输入电流限制设置为600mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_INPUT_CURRENT_LIMIT, 600);
    // 快速充电电流限制设置为2112mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_FAST_CHARGING_CURRENT_LIMIT, 2112);
    // 预充电电流限制设置为192mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_PRECHARGE_CHARGING_CURRENT_LIMIT, 192);
    // 终端充电电流限制设置为320mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_TERMINATION_CHARGING_CURRENT_LIMIT, 320);
    // OTG电流限制设置为500mA
    SY6970->IIC_Write_Device_Value(SY6970->Arduino_IIC_Power::Device_Value::POWER_DEVICE_OTG_CHARGING_LIMIT, 500);
}

void loop()
{
    Serial.printf("--------------------SY6970--------------------\n");
    Serial.printf("System running time: %d\n\n", (uint32_t)millis() / 1000);
    Serial.printf("IIC_Bus.use_count(): %d\n\n", (int32_t)IIC_Bus.use_count());

    Serial.printf("IIC device ID: %#X \n", (int32_t)SY6970->IIC_Device_ID());

    Serial.printf("\nBUS Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_BUS_STATUS)).c_str());
    Serial.printf("BUS Connection Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_BUS_CONNECTION_STATUS)).c_str());
    Serial.printf("Charging Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_CHARGING_STATUS)).c_str());
    Serial.printf("Input Source Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_INPUT_SOURCE_STATUS)).c_str());
    Serial.printf("Input USB Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_INPUT_USB_STATUS)).c_str());
    Serial.printf("System Voltage Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_SYSTEM_VOLTAGE_STATUS)).c_str());
    Serial.printf("Thermal Regulation Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_THERMAL_REGULATION_STATUS)).c_str());

    Serial.printf("\nWatchdog Fault Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_WATCHDOG_FAULT_STATUS)).c_str());
    Serial.printf("OTG Fault Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_OTG_FAULT_STATUS)).c_str());
    Serial.printf("Charging Fault Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_CHARGING_FAULT_STATUS)).c_str());
    Serial.printf("Battery Fault Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_BATTERY_FAULT_STATUS)).c_str());
    Serial.printf("NTC Fault Status: %s \n",
                  (SY6970->IIC_Read_Device_State(SY6970->Arduino_IIC_Power::Status_Information::POWER_NTC_FAULT_STATUS)).c_str());

    Serial.printf("\nInput Voltage: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_INPUT_VOLTAGE));
    Serial.printf("Battery Voltage: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_BATTERY_VOLTAGE));
    Serial.printf("System Voltage: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_SYSTEM_VOLTAGE));
    Serial.printf("NTC Voltage Percentage: %.03f %% \n",
                  (float)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_NTC_VOLTAGE_PERCENTAGE) / 1000.0);
    Serial.printf("Charging Current: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_CHARGING_CURRENT));
    Serial.printf("Thermal Regulation Threshold: %d ^C \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_THERMAL_REGULATION_THRESHOLD));

    Serial.printf("\nCharging Voltage Limit: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_CHARGING_TARGET_VOLTAGE_LIMIT));
    Serial.printf("Minimum System Voltage Limit: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_MINIMUM_SYSTEM_VOLTAGE_LIMIT));
    Serial.printf("OTG Voltage Limit: %d mV \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_OTG_VOLTAGE_LIMIT));
    Serial.printf("Input Current Limit: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_INPUT_CURRENT_LIMIT));
    Serial.printf("Fast Charge Current Limit: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_FAST_CHARGING_CURRENT_LIMIT));
    Serial.printf("Precharge Charge Current Limit: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_PRECHARGE_CHARGING_CURRENT_LIMIT));
    Serial.printf("Termination Charge Current Limit: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_TERMINATION_CHARGING_CURRENT_LIMIT));
    Serial.printf("OTG Current Limit: %d mA \n",
                  (int32_t)SY6970->IIC_Read_Device_Value(SY6970->Arduino_IIC_Power::Value_Information::POWER_OTG_CURRENT_LIMIT));

    Serial.printf("--------------------SY6970--------------------\n\n");

    delay(1000);

    Temp1 = !Temp1;
    if (Temp1 == 0)
    {
    }
    else
    {
    }
}