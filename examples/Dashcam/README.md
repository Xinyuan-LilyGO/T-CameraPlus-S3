# T-CameraPlus-S3 Dashcam (行车记录仪)

基于 LILYGO T-CameraPlus-S3 开发板的行车记录仪固件，将摄像头画面和麦克风音频录制为标准 AVI 文件保存到 microSD 卡，同时在 LCD 上实时预览。

## 硬件要求

| 组件 | 规格 |
|------|------|
| 主控 | LILYGO T-CameraPlus-S3 V1.2 |
| MCU | ESP32-S3，240 MHz，16 MB Flash，8 MB PSRAM |
| 屏幕 | 240×240 ST7789V LCD |
| 摄像头 | OV2640 / OV5640（自动识别） |
| 麦克风 | MP34DT05TR 数字麦克风（PDM） |
| 存储 | microSD 卡（推荐 Class 10 / U3，32 GB+） |
| PMU | SY6970 电源管理 |
| 触摸 | CST816S 触摸屏 |

> **注意：** `board_pins.h` 中的引脚定义对应 V1.2 版本。V1.0 / V1.1 的 SPI、I2C、摄像头和麦克风引脚有所不同，请对照实际板子丝印修改。

## 功能特性

- **循环录像**：自动将视频录制为 AVI 文件（Motion-JPEG 视频 + 16-bit PCM 单声道音频），每段默认 60 秒，存储于 SD 卡 `/dashcam` 目录。
- **循环覆盖**：SD 卡剩余空间低于 150 MB 时自动删除最旧的视频片段，保持不间断录制。
- **实时预览**：录制画面同步显示在 240×240 LCD 上，并叠加状态信息（录制时长、剩余空间、电量、帧率）。
- **拍照快照**：触摸屏幕或按 KEY2 可随时保存 JPEG 照片到 SD 卡 `/photos` 目录。
- **开机自启**：上电后自动开始录制（可在 `config.h` 中关闭）。
- **音频录制**：I2S 数字麦克风同步采集 16 kHz 单声道音频并混入 AVI 文件。

## Flashing



## 操作说明

| 操作 | 功能 |
|------|------|
| 上电 | 自动开始录制（`AUTO_START_RECORDING=1`） |
| 按 **KEY1**（GPIO 17） | 拍摄快照，保存到 `/photos`，播放提示音效 |
| 按 **KEY2**（GPIO 0） | 切换录制开始 / 停止，并发出提示音 |
| **触摸屏幕** | 拍摄快照 |

### LCD 状态叠加层说明

| 图标 / 字段 | 含义 |
|-------------|------|
| `REC` 红点 | 正在录制 |
| `00:01:23` | 当前片段已录制时长 |
| `1234 MB` | SD 卡剩余空间 |
| `85%` | 电池电量 |
| `⚡` | 正在充电 |
| `24 fps` | 当前录制帧率 |

## 文件结构

```
SD 卡
├── dashcam/
│   ├── CLIP_0001.avi
│   ├── CLIP_0002.avi
│   └── ...
└── photos/
    ├── IMG_0001.jpg
    └── ...
```

## 关键配置

所有录制参数集中在 [config.h](config.h) 中，无需修改源码：

| 参数 | 默认值 | 说明 |
|------|--------|------|
| `REC_SEGMENT_SECONDS` | `60` | 每段视频时长（秒） |
| `REC_MIN_FREE_MB` | `150` | SD 最小剩余空间，低于此值触发循环删除 |
| `CAM_JPEG_QUALITY` | `14` | JPEG 质量（越低质量越高，文件越大） |
| `CAM_FRAMESIZE_OV2640` | `SVGA 800×600` | OV2640 分辨率 |
| `CAM_FRAMESIZE_OV5640` | `HD 1280×720` | OV5640 分辨率，受 ESP32-S3 限制，实际录制约 15 fps |
| `AUDIO_ENABLE` | `1` | 是否录制音频 |
| `AUDIO_SAMPLE_RATE` | `16000` | 音频采样率（Hz） |
| `PREVIEW_EVERY_N_FRAMES` | `6` | 每 N 帧更新一次 LCD 预览 |
| `AUTO_START_RECORDING` | `1` | 上电是否自动开始录制 |

---

## 编译与烧录

### PlatformIO（推荐）

**环境要求：**
- [VS Code](https://code.visualstudio.com/) + [PlatformIO IDE 扩展](https://platformio.org/install/ide?install=vscode)
- 或 PlatformIO Core CLI

**步骤：**

```bash
# 1. 进入示例目录
cd examples/Dashcam

# 2. 编译
pio run

# 3. 烧录（请先连接开发板）
pio run -t upload

# 4. 打开串口监视器（115200 波特率）
pio device monitor

# 一键编译 + 烧录 + 监视
pio run -t upload && pio device monitor
```

编译完成后，`merge_bin.py` 后处理脚本会自动将 bootloader、分区表和应用固件合并为单个可烧录文件：

```
firmware_out/T-CameraPlus-S3_Dashcam.bin
```

**直接烧录合并固件（无需编译环境）：**

```bash
esptool.py --chip esp32s3 --baud 921600 write_flash 0x0 firmware_out/T-CameraPlus-S3_Dashcam.bin
```

---

### Arduino IDE

**环境要求：**
- Arduino IDE 2.x
- ESP32 Arduino 核心 2.0.14（[安装说明](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)）

**安装依赖库（库管理器搜索安装）：**

| 库名 | 版本 |
|------|------|
| LovyanGFX | ^1.1.16 |
| JPEGDEC | ^1.6.2 |
| XPowersLib | ^0.2.6 |
| OneButton | ^2.5.0 |

**开发板设置（工具菜单）：**

| 选项 | 值 |
|------|-----|
| Board | ESP32S3 Dev Module |
| Flash Size | 16MB (128Mb) |
| Partition Scheme | 自定义（需手动导入 `partitions.csv`） |
| PSRAM | OPI PSRAM |
| Flash Mode | QIO 80MHz |
| USB Mode | Hardware CDC and JTAG |
| CPU Frequency | 240MHz (WiFi) |
| Upload Speed | 921600 |

**步骤：**

1. 打开 `Dashcam.ino`。
2. 按上表配置开发板选项。
3. 点击 **上传** 按钮编译并烧录。
4. 打开 **串口监视器**，波特率设为 `115200`。

> **提示：** Arduino IDE 不支持自定义分区表文件的直接导入，建议将 `partitions.csv` 内容对应的分区方案预先添加到 Arduino 核心的 `boards.txt` 或使用 PlatformIO 以避免分区设置问题。

---

## 架构说明

固件使用 FreeRTOS 双核并行：

| 任务 | 运行核心 | 优先级 | 职责 |
|------|----------|--------|------|
| `recordTask` | Core 1 | 5 | 摄像头采集、AVI 封装、SD 写入 |
| `uiTask` | Core 0 | 3 | LCD 预览渲染、触摸检测、按键轮询、PMU 状态 |
| mic task（内部） | Core 0 | — | I2S 采集 → FreeRTOS Stream Buffer |

LCD 和 microSD 共用同一条 SPI 总线，通过互斥锁（`spibus::Guard`）保证访问安全。

## 单元测试（AVI 封装器，仅 PC 端）

AVI 写入模块可在无硬件的环境下独立测试：

```bash
g++ -std=c++14 -I../../src test/host/test_avi.cpp avi_writer.cpp -o test_avi
./test_avi
```

## 常见问题

**录制不启动 / LCD 显示 "NO SD CARD"**
- 检查 SD 卡是否插入，格式为 FAT32 或 exFAT。
- SD 卡容量建议 32 GB 以上，Class 10 / U3。

**无声音**
- 检查 `config.h` 中 `AUDIO_ENABLE` 是否为 `1`。
- 检查 `AUDIO_I2S_CHANNEL` 是否与板子麦克风通道匹配。

**帧率偏低**
- 减小 `CAM_JPEG_QUALITY`（数值增大）可降低文件大小，提升帧率。
- 增大 `PREVIEW_EVERY_N_FRAMES` 可减少 LCD 占用 SPI 总线的时间，释放更多带宽给 SD 写入。

**V1.0 / V1.1 板子无法正常工作**
- `board_pins.h` 中的引脚定义基于 V1.2，请对照官方原理图修改相应引脚号。
