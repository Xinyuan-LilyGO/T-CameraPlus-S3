// =====================================================================
//  spi_bus.cpp  -  see spi_bus.h
// =====================================================================
#include "spi_bus.h"
#include "board_pins.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

namespace spibus {

static SemaphoreHandle_t s_mux = nullptr;

void begin() {
    if (!s_mux) s_mux = xSemaphoreCreateMutex();
    SPI.begin(PIN_SPI_SCLK, PIN_SPI_MISO, PIN_SPI_MOSI);
}

void lock() {
    if (s_mux) xSemaphoreTake(s_mux, portMAX_DELAY);
}

void unlock() {
    if (s_mux) xSemaphoreGive(s_mux);
}

SPIClass &spi() { return SPI; }

}  // namespace spibus
