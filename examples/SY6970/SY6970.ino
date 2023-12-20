/*
 * @Description: SY6970.cpp
 * @version: V1.0.0
 * @Author: Lewis He (lewishe@outlook.com)
 * @Date: 2023-09-13 14:32:42
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-12-12 11:32:08
 * @License: GPL 3.0
 */
#include <XPowersLib.h>

PowersSY6970 PMU;

#define CONFIG_PMU_SDA 1
#define CONFIG_PMU_SCL 2
#define CONFIG_PMU_IRQ 47

const uint8_t i2c_sda = CONFIG_PMU_SDA;
const uint8_t i2c_scl = CONFIG_PMU_SCL;
const uint8_t pmu_irq_pin = CONFIG_PMU_IRQ;
uint32_t cycleInterval;

bool OTG_Flag = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(GPIO_NUM_17, INPUT_PULLUP);

    bool result = PMU.init(Wire, i2c_sda, i2c_scl, SY6970_SLAVE_ADDRESS);

    if (result == false)
    {
        while (1)
        {
            Serial.println("PMU is not online...");
            delay(50);
        }
    }

    // To obtain voltage data, the ADC must be enabled first
    PMU.enableADCMeasure();

    // Set Charge Voltage Limit, Range:3840 ~ 4608mV ,step:16 mV
    PMU.setChargeTargetVoltage(4208);

    // Set Fast Charge Current Limit, Range:0~5056mA ,step:64mA
    PMU.setChargerConstantCurr(320); // 普通锂电池限制充电450mA

    // Set Precharge Current Limit , Range: 64mA ~ 1024mA ,step:64mA
    PMU.setPrechargeCurr(192);

    // Set Termination Current Limit , Range: 64mA ~ 1024mA ,step:64mA
    PMU.setTerchargeCurr(128);

    // The OTG function needs to enable OTG, and set the OTG control pin to HIGH
    // After OTG is enabled, if an external power supply is plugged in, OTG will be turned off

    // PMU.enableOTG();
    // PMU.disableOTG();
    // pinMode(OTG_ENABLE_PIN, OUTPUT);
    // digitalWrite(OTG_ENABLE_PIN, HIGH);
}

void loop()
{
    if (digitalRead(GPIO_NUM_17) == 0)
    {
        OTG_Flag = !OTG_Flag;

        if (OTG_Flag == 0)
        {
            PMU.disableOTG();

            // Set Charge Voltage Limit, Range:3840 ~ 4608mV ,step:16 mV
            PMU.setChargeTargetVoltage(4208);

            // Set Fast Charge Current Limit, Range:0~5056mA ,step:64mA
            PMU.setChargerConstantCurr(320);

            // Set Precharge Current Limit , Range: 64mA ~ 1024mA ,step:64mA
            PMU.setPrechargeCurr(192);

            // Set Termination Current Limit , Range: 64mA ~ 1024mA ,step:64mA
            PMU.setTerchargeCurr(128);
        }
        if (OTG_Flag == 1)
        {
            PMU.enableOTG();
        }
        delay(1000);
    }

    // SY6970 When VBUS is input, the battery voltage detection will not take effect
    if (millis() > cycleInterval)
    {
        Serial.printf("\n------------------------------------------------\n");

        Serial.printf("%s\n", PMU.isVbusIn() ? "Connection successful" : "Connection failure");

        Serial.printf("\n");

        Serial.printf("Bus mode: %s \n", PMU.getBusStatusString());
        Serial.printf("Charge mode: %s \n", PMU.getChargeStatusString());

        Serial.printf("\n");

        Serial.printf("Total supply voltage: %d mv\n", PMU.getVbusVoltage());
        Serial.printf("Battery voltage: %d mv\n", PMU.getBattVoltage());
        Serial.printf("System voltage: %d mv\n", PMU.getSystemVoltage());

        Serial.printf("\n");

        Serial.printf("Charge Voltage Limit: %d mv\n", PMU.getChargeTargetVoltage());
        Serial.printf("Fast Charge Current Limit: %d ma\n", PMU.getChargerConstantCurr());
        Serial.printf("Precharge Current Limit: %d ma\n", PMU.getPrechargeCurr());
        Serial.printf("Termination Current Limit: %d ma\n", PMU.getTerchargeCurr());

        Serial.printf("\n");

        // Serial.printf("%s \n", PMU.getNTCStatusString());

        // // Charge Mode Fault Status
        // // Serial.printf("xxx:%d\n", PMU.isChargeNormal());
        // switch (PMU.isChargeNormal())
        // {
        // case 0x00:
        //     Serial.printf("Normal: Charge Mode is normal\n");
        //     break;
        // case 0x10:
        //     Serial.printf("Error: Input fault (BUS OVP or VBAT<BUS<3.8V)\n");
        //     break;
        // case 0x18:
        //     Serial.printf("Error: Charge Safety Timer Expiration\n");
        //     break;
        // case 0x20:
        //     Serial.printf("Error: Thermal shutdown\n");
        //     break;

        // default:
        //     break;
        // }

        // // Watchdog Fault status
        // switch (PMU.isWatchdogNormal())
        // {
        // case 0:
        //     Serial.printf("Error: Watchdog timer expiration\n");
        //     break;
        // case 1:
        //     Serial.printf("Normal: Watch dog is normal\n");
        //     break;

        // default:
        //     break;
        // }

        // // Boost Mode Fault Status
        // switch (PMU.isBoostNormal())
        // {
        // case 0:
        //     Serial.printf("Error: BUS overloaded in OTG, or BUS OVP, or battery is too low\n");
        //     break;
        // case 1:
        //     Serial.printf("Normal: Boost Mode is normal\n");
        //     break;

        // default:
        //     break;
        // }

        // // Battery Fault Status
        // switch (PMU.isBatteryNormal())
        // {
        // case 0:
        //     // BatOVP occurs when the full charge voltage value set by the charging IC
        //     // in the presence of Vbus is less than the current battery voltage.
        //     Serial.printf("Error: BAT OVP\n");
        //     break;
        // case 1:
        //     Serial.printf("Normal: Battery Fault is normal\n");
        //     break;

        // default:
        //     break;
        // }

        Serial.printf("------------------------------------------------\n");

        cycleInterval = millis() + 2500;
    }
}
