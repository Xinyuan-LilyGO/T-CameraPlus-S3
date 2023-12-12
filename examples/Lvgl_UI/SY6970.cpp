/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-17 09:42:24
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-17 16:43:58
 * @License: GPL 3.0
 */
#include "custom.h"
#include "pin_config.h"
#include "SY6970.h"

PowersSY6970 PMU;

bool SY6970_Initialization(void)
{
    if (PMU.init(Wire, SY6970_SDA, SY6970_SCL, SY6970_SLAVE_ADDRESS) == false)
    {
        My_UI.SY6970_Initialization_Flag = false;
        return false;
    }
    else
    {
        My_UI.SY6970_Initialization_Flag = true;

        // To obtain voltage data, the ADC must be enabled first
        PMU.enableADCMeasure();

        // Set Charge Voltage Limit, Range:3840 ~ 4608mV ,step:16 mV
        PMU.setChargeTargetVoltage(My_UI.Battery_Control_Charge_Voltage_Limit);

        // Set Fast Charge Current Limit, Range:0~5056mA ,step:64mA
        PMU.setChargerConstantCurr(My_UI.Battery_Control_Fast_Charge_Current_Limit); // 普通锂电池限制充电450mA

        // Set Precharge Current Limit , Range: 64mA ~ 1024mA ,step:64mA
        PMU.setPrechargeCurr(My_UI.Battery_Control_Precharge_Charge_Current_Limit);

        // Set Termination Current Limit , Range: 64mA ~ 1024mA ,step:64mA
        PMU.setTerchargeCurr(My_UI.Battery_Control_Termination_Charge_Current_Limit);

        PMU.disableOTG();

        My_UI.Battery_Control_OTG_Mode_Flag = My_UI.Battery_Control_OTG_OFF;

        My_UI.Battery_Information_Bus_Mode = PMU.getBusStatusString();
        My_UI.Battery_Information_Charge_Mode = PMU.getChargeStatusString();
        My_UI.Battery_Information_Total_Supply_Voltage = PMU.getVbusVoltage();
        My_UI.Battery_Information_Battery_Voltage = PMU.getBattVoltage();
        My_UI.Battery_Information_System_Voltage = PMU.getSystemVoltage();
        My_UI.Battery_Information_Charge_Voltage_Limit = PMU.getChargeTargetVoltage();
        My_UI.Battery_Information_Fast_Charge_Current_Limit = PMU.getChargerConstantCurr();
        My_UI.Battery_Information_Precharge_Charge_Current_Limit = PMU.getPrechargeCurr();
        My_UI.Battery_Information_Termination_Charge_Current_Limit = PMU.getTerchargeCurr();

        return true;
    }
}

void My_UI_Battery_Loop(void)
{
    if (My_UI.Battery_Information_Refresh_Flag == true)
    {
        if (My_UI.SY6970_Initialization_Flag == true)
        {
            My_UI.Battery_Information_Bus_Mode = PMU.getBusStatusString();
            My_UI.Battery_Information_Charge_Mode = PMU.getChargeStatusString();
            My_UI.Battery_Information_Total_Supply_Voltage = PMU.getVbusVoltage();
            My_UI.Battery_Information_Battery_Voltage = PMU.getBattVoltage();
            My_UI.Battery_Information_System_Voltage = PMU.getSystemVoltage();
            My_UI.Battery_Information_Charge_Voltage_Limit = PMU.getChargeTargetVoltage();
            My_UI.Battery_Information_Fast_Charge_Current_Limit = PMU.getChargerConstantCurr();
            My_UI.Battery_Information_Precharge_Charge_Current_Limit = PMU.getPrechargeCurr();
            My_UI.Battery_Information_Termination_Charge_Current_Limit = PMU.getTerchargeCurr();

            lv_table_set_cell_value(guider_ui.Battery_table_1, 0, 1, (My_UI.Battery_Information_Bus_Mode).c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 1, 1, (My_UI.Battery_Information_Charge_Mode).c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 2, 1, ((String)My_UI.Battery_Information_Total_Supply_Voltage + " mV").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 3, 1, ((String)My_UI.Battery_Information_Battery_Voltage + " mV").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 4, 1, ((String)My_UI.Battery_Information_System_Voltage + " mV").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 5, 1, ((String)My_UI.Battery_Information_Charge_Voltage_Limit + " mV").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 6, 1, ((String)My_UI.Battery_Information_Fast_Charge_Current_Limit + " mA").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 7, 1, ((String)My_UI.Battery_Information_Precharge_Charge_Current_Limit + " mA").c_str());
            lv_table_set_cell_value(guider_ui.Battery_table_1, 8, 1, ((String)My_UI.Battery_Information_Termination_Charge_Current_Limit + " mA").c_str());

            if (My_UI.Battery_Control_OTG_Mode_Flag == My_UI.Battery_Control_OTG_ON)
            {
                lv_table_set_cell_value(guider_ui.Battery_table_1, 9, 1, "ON");
            }
            else
            {
                lv_table_set_cell_value(guider_ui.Battery_table_1, 9, 1, "OFF");
            }

            // Update current screen layout.
            lv_obj_update_layout(guider_ui.Battery); // 刷新电池窗口的界面
        }
    }
}

void My_UI_Window_StatusBar_Charge_State_Refresh(void)
{
    if (My_UI.SY6970_Initialization_Flag == true)
    {
        My_UI.Battery_Information_Charge_Mode = PMU.getChargeStatusString();
        My_UI.Battery_Information_Battery_Voltage = PMU.getBattVoltage();              // 获取电池电压
        My_UI.Battery_Information_Charge_Voltage_Limit = PMU.getChargeTargetVoltage(); // 获取目标充电电压

        if (My_UI.Battery_Information_Charge_Voltage_Limit > My_UI.Battery_Minimum_Voltage &&
            My_UI.Battery_Information_Battery_Voltage > My_UI.Battery_Minimum_Voltage)
        {
            My_UI.Battery_Voltage_Percentage = (((float)My_UI.Battery_Information_Battery_Voltage -
                                                 (float)My_UI.Battery_Minimum_Voltage) /
                                                ((float)My_UI.Battery_Information_Charge_Voltage_Limit -
                                                 (float)My_UI.Battery_Minimum_Voltage)) *
                                               100.0;
        }
        else
        {
            My_UI.Battery_Voltage_Percentage = 0;
        }

        if (My_UI.Battery_Information_Charge_Mode == "Not Charge") // 如果不在充电
        {
            if (My_UI.Battery_Voltage_Percentage >= 0 && My_UI.Battery_Voltage_Percentage < 25)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Level_1;
            }
            if (My_UI.Battery_Voltage_Percentage >= 25 && My_UI.Battery_Voltage_Percentage < 25)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Level_1;
            }
            if (My_UI.Battery_Voltage_Percentage >= 25 && My_UI.Battery_Voltage_Percentage < 50)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Level_2;
            }
            if (My_UI.Battery_Voltage_Percentage >= 50 && My_UI.Battery_Voltage_Percentage < 75)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Level_3;
            }
            if (My_UI.Battery_Voltage_Percentage >= 75 && My_UI.Battery_Voltage_Percentage <= 100)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Full;
            }
            if (My_UI.Battery_Voltage_Percentage > 100)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_OFF_Battery_Full;
            }
        }

        if (My_UI.Battery_Information_Charge_Mode == "Fast Charge" ||
            My_UI.Battery_Information_Charge_Mode == "Pre Charge" ||
            My_UI.Battery_Information_Charge_Mode == "Ter Charge") // 如果在充电
        {
            // Serial.println(My_UI.Battery_Voltage_Percentage);
            // Serial.println(My_UI.Battery_Information_Battery_Voltage);
            // Serial.println(My_UI.Battery_Information_Charge_Voltage_Limit);
            // Serial.println(My_UI.Battery_Minimum_Voltage);

            if (My_UI.Battery_Voltage_Percentage >= 0 && My_UI.Battery_Voltage_Percentage < 25)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Level_1;
            }
            if (My_UI.Battery_Voltage_Percentage >= 25 && My_UI.Battery_Voltage_Percentage < 25)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Level_1;
            }
            if (My_UI.Battery_Voltage_Percentage >= 25 && My_UI.Battery_Voltage_Percentage < 50)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Level_2;
            }
            if (My_UI.Battery_Voltage_Percentage >= 50 && My_UI.Battery_Voltage_Percentage < 75)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Level_3;
            }
            if (My_UI.Battery_Voltage_Percentage >= 75 && My_UI.Battery_Voltage_Percentage <= 100)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Full;
            }
            if (My_UI.Battery_Voltage_Percentage > 100)
            {
                My_UI.System_State_Of_Charge_Flag = My_UI.System_State_Of_Charge_ON_Battery_Full;
            }
        }
    }
    if (My_UI.Battery_Information_Charge_Mode == "Unknown")
    {
    }

    switch (My_UI.System_State_Of_Charge_Flag)
    {
    case My_UI.System_State_Of_Charge_ON_Battery_Free:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_EMPTY LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_1:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_1 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_2:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_2 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Level_3:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_3 LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_1:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_1);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_2:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_2);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Level_3:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_3);
        break;
    case My_UI.System_State_Of_Charge_ON_Battery_Full:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_FULL LV_SYMBOL_CHARGE);
        break;
    case My_UI.System_State_Of_Charge_OFF_Battery_Full:
        lv_label_set_text(guider_ui.Window_StatusBar_label_1, LV_SYMBOL_BATTERY_FULL);
        break;

    default:
        break;
    }

    // Update current screen layout.
    lv_obj_update_layout(lv_scr_act()); // 刷新当前屏幕（如果当前屏幕没有加装窗口状态栏刷新函数，系统就会强制闪退重启）
}
