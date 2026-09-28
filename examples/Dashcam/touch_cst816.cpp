// =====================================================================
//  touch_cst816.cpp  -  see touch_cst816.h
// =====================================================================
#include "touch_cst816.h"
#include "board_pins.h"
#include <Arduino.h>
#include <Wire.h>

namespace touch {

static bool s_present = false;

static bool readRegs(uint8_t reg, uint8_t *buf, uint8_t len) {
    Wire.beginTransmission(TOUCH_ADDR_CST816);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return false;
    uint8_t got = Wire.requestFrom((int)TOUCH_ADDR_CST816, (int)len);
    if (got != len) return false;
    for (uint8_t i = 0; i < len; ++i) buf[i] = Wire.read();
    return true;
}

bool begin() {
#if PIN_TOUCH_RST >= 0
    // Hardware reset pulse (CST816S needs RST toggled at power-up).
    pinMode(PIN_TOUCH_RST, OUTPUT);
    digitalWrite(PIN_TOUCH_RST, LOW);
    delay(20);
    digitalWrite(PIN_TOUCH_RST, HIGH);
    delay(60);
#else
    delay(80);  // V1.2: no RST pin, allow touch IC to self-boot
#endif

    // Probe: ChipID register 0xA7 should respond.
    uint8_t id = 0;
    s_present = readRegs(0xA7, &id, 1);
    log_i("touch CST816S %s (id=0x%02x)", s_present ? "present" : "absent", id);
    return s_present;
}

bool present() { return s_present; }

bool read(uint16_t *x, uint16_t *y) {
    if (!s_present) return false;
    uint8_t b[5];
    // reg 0x02 = finger count, 0x03..0x06 = X/Y (12-bit, big-endian nibble hi)
    if (!readRegs(0x02, b, sizeof(b))) return false;
    uint8_t fingers = b[0] & 0x0F;
    if (fingers == 0) return false;
    uint16_t rx = ((uint16_t)(b[1] & 0x0F) << 8) | b[2];
    uint16_t ry = ((uint16_t)(b[3] & 0x0F) << 8) | b[4];
    if (rx > 239) rx = 239;
    if (ry > 239) ry = 239;
    if (x) *x = rx;
    if (y) *y = ry;
    return true;
}

}  // namespace touch
