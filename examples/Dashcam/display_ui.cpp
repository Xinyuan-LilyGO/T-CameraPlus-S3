// =====================================================================
//  display_ui.cpp  -  LovyanGFX ST7789 240x240 preview + status overlay
//
//  The LCD shares the SPI bus with the SD card (bus_shared = true).
//  All draw calls must be made while holding spibus::lock() —
//  renderFrame(), splash(), and message() each acquire it via Guard.
// =====================================================================
#include "display_ui.h"
#include "spi_bus.h"
#include "board_pins.h"
#include <Arduino.h>
#include <LovyanGFX.hpp>
#include <JPEGDEC.h>

namespace display {

// ---- LovyanGFX device: ST7789 240x240 on the shared SPI bus ---------
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7789 _panel;
    lgfx::Bus_SPI      _bus;
public:
    LGFX() {
        {
            auto cfg = _bus.config();
            cfg.spi_host    = SPI2_HOST;        // same host as Arduino SPI / SD
            cfg.spi_mode    = 0;
            cfg.freq_write  = 40000000;
            cfg.freq_read   = 16000000;
            cfg.spi_3wire   = false;
            cfg.use_lock    = true;
            cfg.dma_channel = SPI_DMA_CH_AUTO;
            cfg.pin_sclk    = PIN_SPI_SCLK;
            cfg.pin_mosi    = PIN_SPI_MOSI;
            cfg.pin_miso    = PIN_SPI_MISO;
            cfg.pin_dc      = PIN_LCD_DC;
            _bus.config(cfg);
            _panel.setBus(&_bus);
        }
        {
            auto cfg = _panel.config();
            cfg.pin_cs          = PIN_LCD_CS;
            cfg.pin_rst         = PIN_LCD_RST;
            cfg.pin_busy        = -1;
            cfg.memory_width    = LCD_WIDTH;
            cfg.memory_height   = LCD_HEIGHT;
            cfg.panel_width     = LCD_WIDTH;
            cfg.panel_height    = LCD_HEIGHT;
            cfg.offset_x        = 0;
            cfg.offset_y        = 0;
            cfg.offset_rotation = 0;            // 180° — matches original setRotation(2)
            cfg.dummy_read_pixel = 8;
            cfg.dummy_read_bits  = 1;
            cfg.readable        = false;
            cfg.invert          = true;         // ST7789 requires inversion
            cfg.rgb_order       = false;
            cfg.dlen_16bit      = false;
            cfg.bus_shared      = true;         // shared with SD card
            _panel.config(cfg);
        }
        setPanel(&_panel);
    }
};

static LGFX tft;

// ---- JPEGDEC decoder → PSRAM buffer → pushImageRotateZoom ------------------
// HD (1280×720) at 1/4 scale → 320×180 decode buffer, then zoomed to 240px wide.
static JPEGDEC   s_jpeg;
static uint16_t *s_decBuf = nullptr;  // PSRAM decode buffer (RGB565)
static int       s_decW   = 0;        // actual decoded width  (set per-frame)
static int       s_decH   = 0;        // actual decoded height (set per-frame)

static int jpegToBufferCB(JPEGDRAW *pDraw) {
    uint16_t *dst = s_decBuf + pDraw->y * s_decW + pDraw->x;
    uint16_t *src = (uint16_t *)pDraw->pPixels;
    for (int row = 0; row < pDraw->iHeight; row++, dst += s_decW, src += pDraw->iWidth)
        memcpy(dst, src, pDraw->iWidth * sizeof(uint16_t));
    return 1;
}

// RGB565 colors — must be int32_t so LovyanGFX routes through convert_rgb565().
// uint32_t would be routed through convert_rgb888(), misinterpreting the value.
static const int32_t C_BLACK  = TFT_BLACK;
static const int32_t C_WHITE  = TFT_WHITE;
static const int32_t C_RED    = TFT_RED;
static const int32_t C_GREEN  = TFT_GREEN;
static const int32_t C_YELLOW = TFT_YELLOW;
static const int32_t C_GREY   = 0x8410;

bool begin() {
    // HD 1280×720 at JPEG_SCALE_QUARTER → 320×180 pixels × 2 bytes = 115 200 B
    s_decBuf = (uint16_t *)ps_malloc(320 * 180 * sizeof(uint16_t));
    if (!s_decBuf) log_e("display: decode buffer alloc failed");

    backlight(false);
    {
        spibus::Guard g;
        tft.init();
        tft.startWrite();
        tft.fillScreen(TFT_BLACK);
        tft.endWrite();
    }
    backlight(true);
    return true;
}

void backlight(bool on) {
    pinMode(PIN_LCD_BL, OUTPUT);
    digitalWrite(PIN_LCD_BL, on ? HIGH : LOW);
}

static void drawOverlay(const Overlay &ov) {
    // top status strip
    tft.setFont(&lgfx::fonts::efontCN_16_b);
    tft.fillRect(0, 0, LCD_WIDTH, 5 + tft.fontHeight(), C_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(C_WHITE);

    if (ov.recording) {
        tft.fillCircle(8, 13, 4, C_RED);
        tft.setTextColor(C_RED);
        tft.setCursor(18, 5);
        tft.print("REC");
    } else {
        tft.fillCircle(8, 13, 4, C_GREY);
        tft.setTextColor(C_GREY);
        tft.setCursor(18, 5);
        tft.print("IDLE");
    }

    // elapsed mm:ss
    char ts[12];
    snprintf(ts, sizeof(ts), "%02lu:%02lu",
             (unsigned long)(ov.elapsedSec / 60), (unsigned long)(ov.elapsedSec % 60));
    tft.setTextColor(C_WHITE);
    tft.setCursor(75, 5);
    tft.print(ts);

    // fps
    char fb[12];
    snprintf(fb, sizeof(fb), "%2.0ff", ov.fps);
    tft.setCursor(145, 5);
    tft.print(fb);

    // battery (top-right)
    int px = 200, py = 8;
    tft.drawRect(px, py, 32, 13, C_WHITE);
    tft.fillRect(px + 32, py + 5, 2, 5, C_WHITE);
    if (ov.battPct >= 0) {
        int bw = (ov.battPct * 30) / 100;
        uint32_t col = ov.battPct > 20 ? (ov.charging ? C_GREEN : C_WHITE) : C_RED;
        tft.fillRect(px + 1, py + 1, bw, 11, col);
    } else {
        tft.setCursor(px + 12, py + 3);
        tft.setTextColor(C_GREY);
        tft.setFont(&lgfx::fonts::Font0);
        tft.print("?");
        tft.setFont(&lgfx::fonts::efontCN_16_b);
    }

    // bottom strip: free space on card
    tft.fillRect(0, 210, LCD_WIDTH, 30, C_BLACK);
    char fs[24];
    snprintf(fs, sizeof(fs), "SD free: %lu MB", (unsigned long)ov.freeMB);
    tft.setTextColor(ov.freeMB < 200 ? C_YELLOW : C_GREY);
    tft.setCursor(6, 220);
    tft.print(fs);
    tft.setFont(&lgfx::fonts::Font0);
}

void renderFrame(const uint8_t *jpg, size_t len, const Overlay &ov) {
    static constexpr int   CONT_Y  = 18;
    static constexpr int   CONT_H  = LCD_HEIGHT - 18 - 14;   // 208 px
    static constexpr float DST_CX  = LCD_WIDTH  / 2.0f;      // 120
    static constexpr float DST_CY  = CONT_Y + CONT_H / 2.0f; // 122

    if (!s_decBuf) return;

    spibus::Guard g;
    tft.startWrite();

    if (s_jpeg.openRAM((uint8_t *)jpg, (int)len, jpegToBufferCB)) {
        s_jpeg.setPixelType(RGB565_BIG_ENDIAN);

        // 1/4 scale: 1280×720 → 320×180, fits in the pre-allocated buffer.
        s_decW = s_jpeg.getWidth()  / 4;
        s_decH = s_jpeg.getHeight() / 4;
        s_jpeg.decode(0, 0, JPEG_SCALE_QUARTER);
        s_jpeg.close();

        // Scale proportionally so output width = LCD_WIDTH (240 px).
        // For 320×180 → zoom 0.75 → output 240×135, centered at (120, 122).
        float zoom = (float)LCD_WIDTH / (float)s_decW;
        tft.pushImageRotateZoom(
            DST_CX,          DST_CY,          // destination centre on screen
            s_decW / 2.0f,   s_decH / 2.0f,  // source pivot  (image centre)
            0.0f,                             // angle (no rotation)
            zoom,            zoom,            // uniform scale
            s_decW,          s_decH,          // decoded image size
            s_decBuf                          // RGB565 pixel buffer (PSRAM)
        );
    }

    drawOverlay(ov);
    tft.endWrite();
}

void splash(const char *l1, const char *l2) {
    spibus::Guard g;
    tft.startWrite();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(20, 95);  tft.print(l1 ? l1 : "");
    tft.setTextSize(1);
    tft.setCursor(20, 125); tft.print(l2 ? l2 : "");
    tft.endWrite();
}

void message(const char *msg) {
    spibus::Guard g;
    tft.startWrite();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(2);
    tft.setCursor(10, 110);
    tft.print(msg ? msg : "");
    tft.endWrite();
}

}  // namespace display
