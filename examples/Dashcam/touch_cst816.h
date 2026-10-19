// =====================================================================
//  touch_cst816.h  -  CST816S capacitive touch (I2C, polled)
//
//  Uses the shared Wire bus (IO1/IO2). To avoid cross-task I2C races, only
//  poll touch (and the PMU) from a single task - here, the UI task.
// =====================================================================
#pragma once
#include <stdint.h>

namespace touch {

bool begin();                               // reset chip, probe presence
bool present();

// Returns true while a finger is down; fills x/y (0..239) when it is.
bool read(uint16_t *x, uint16_t *y);

}  // namespace touch
