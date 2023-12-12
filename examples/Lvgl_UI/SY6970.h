/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-17 09:51:28
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-10-17 15:20:14
 * @License: GPL 3.0
 */
#pragma once

#include "XPowersLib.h"

bool SY6970_Initialization(void);
void My_UI_Battery_Loop(void);
void My_UI_Window_StatusBar_Charge_State_Refresh(void);

extern PowersSY6970 PMU;
