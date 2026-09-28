// =====================================================================
//  power_sy6970.cpp  -  see power_sy6970.h
// =====================================================================
#include "power_sy6970.h"
#include "board_pins.h"
#include <Arduino.h>
#include <Wire.h>
#include <XPowersLib.h>

namespace power {

static PowersSY6970 s_pmu;
static bool  s_present = false;
static float s_volt = 0.0f;
static bool  s_usb = false;
static bool  s_chg = false;

bool begin() {
    // Reuse the already-initialized Wire bus (IO1/IO2).
    s_present = s_pmu.init(Wire, PIN_I2C_SDA, PIN_I2C_SCL, SY6970_SLAVE_ADDRESS);
    if (!s_present) { log_w("SY6970 not found"); return false; }

    s_pmu.enableADCMeasure();          // required before voltage reads
    s_pmu.setChargeTargetVoltage(4208);
    s_pmu.setChargerConstantCurr(1024);
    s_pmu.enableCharge();
    log_i("SY6970 PMU ready");
    return true;
}

bool present() { return s_present; }

void update() {
    if (!s_present) return;
    s_volt = s_pmu.getBattVoltage() / 1000.0f;   // mV -> V
    s_usb  = s_pmu.isVbusIn();
    // SY6970 has no fuel gauge; treat "USB present + not yet full" as charging.
    s_chg  = s_usb && (s_volt > 2.5f) && (s_volt < 4.15f);
}

float batteryVoltage() { return s_volt; }

int batteryPercent() {
    if (!s_present || s_volt < 2.5f) return -1;   // no/!connected battery
    // crude LiPo curve: 3.30V -> 0%, 4.20V -> 100%
    float pct = (s_volt - 3.30f) / (4.20f - 3.30f) * 100.0f;
    if (pct < 0) pct = 0; if (pct > 100) pct = 100;
    return (int)(pct + 0.5f);
}

bool usbConnected() { return s_usb; }
bool charging()     { return s_chg; }

}  // namespace power
