/*
 * @Description: None
 * @version: V1.0.0
 * @Author: LILYGO_L
 * @Date: 2023-10-18 19:00:09
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-11-21 13:42:05
 * @License: GPL 3.0
 */

#pragma once

// OV2640 pixel format
enum class OV2640_Pixel_Format
{
    PIXFORMAT_RGB565,    // 2BPP/RGB565
    PIXFORMAT_YUV422,    // 2BPP/YUV422
    PIXFORMAT_YUV420,    // 1.5BPP/YUV420
    PIXFORMAT_GRAYSCALE, // 1BPP/GRAYSCALE
    PIXFORMAT_JPEG,      // JPEG/COMPRESSED
    PIXFORMAT_RGB888,    // 3BPP/RGB888
    PIXFORMAT_RAW,       // RAW
    PIXFORMAT_RGB444,    // 3BP2P/RGB444
    PIXFORMAT_RGB555,    // 3BP2P/RGB555
};

bool OV2640_Initialization(OV2640_Pixel_Format pixel_format);
void startCameraServer();
void OV2640_Loop(void);
