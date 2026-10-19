// =====================================================================
//  spi_bus.h  -  the LCD and the microSD card share one SPI bus.
//  All access must be serialized through this mutex so an LCD redraw can
//  never interleave with an in-progress SD block write (or vice-versa).
// =====================================================================
#pragma once
#include <SPI.h>

namespace spibus {

void      begin();         // SPI.begin(SCLK,MISO,MOSI) + create the mutex
void      lock();          // blocking acquire
void      unlock();
SPIClass &spi();           // the shared SPIClass instance

// RAII helper:  { spibus::Guard g; ...bus ops... }
struct Guard {
    Guard()  { lock(); }
    ~Guard() { unlock(); }
};

}  // namespace spibus
