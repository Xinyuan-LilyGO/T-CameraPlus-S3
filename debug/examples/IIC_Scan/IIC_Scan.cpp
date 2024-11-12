/*
 * @Description: None
 * @version: None
 * @Author: None
 * @Date: 2023-07-01 15:48:22
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-08-24 16:12:22
 * @License: MIT
 */
#include <Arduino.h>
#include <Wire.h>

#define SDA 1
#define SCL 2

void deviceScan(TwoWire *_port, Stream *stream)
{
    uint8_t err, addr;
    int nDevices = 0;
    for (addr = 1; addr < 127; addr++)
    {
        _port->beginTransmission(addr);
        err = _port->endTransmission();
        if (err == 0)
        {
            stream->print("I2C device found at address 0x");
            if (addr < 16)
                stream->print("0");
            stream->print(addr, HEX);
            stream->println(" !");
            nDevices++;
        }
        else if (err == 4)
        {
            stream->print("Unknow error at address 0x");
            if (addr < 16)
                stream->print("0");
            stream->println(addr, HEX);
        }
    }
    if (nDevices == 0)
        stream->println("No I2C devices found\n");
    else
        stream->println("Done\n");
}

void setup()
{
    Serial.begin(115200);
    Wire.begin(SDA, SCL);
}

void loop()
{
    deviceScan(&Wire, &Serial);
    delay(1000);
}
