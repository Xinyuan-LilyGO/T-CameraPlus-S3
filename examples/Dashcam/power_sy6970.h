// =====================================================================
//  power_sy6970.h  -  SY6970 PMU / charger (battery + USB status)
//
//  Shares the Wire bus; poll only from the UI task (see touch_cst816.h).
// =====================================================================
#pragma once
#include <stdint.h>

namespace power {

bool  begin();
bool  present();
void  update();             // refresh cached readings (call periodically)

float batteryVoltage();     // volts (0 if unknown)
int   batteryPercent();     // 0..100, or -1 if unknown
bool  usbConnected();
bool  charging();

}  // namespace power
