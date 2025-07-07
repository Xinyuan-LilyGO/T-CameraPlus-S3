<!--
 * @Description: None
 * @Author: LILYGO_L
 * @Date: 2023-09-11 16:13:14
 * @LastEditTime: 2025-07-07 11:35:41
 * @License: GPL 3.0
-->
<h1 align = "center">T-CameraPlus-S3</h1>

<p align="center" width="100%">
    <img src="image/13.jpg" alt="">
</p>

<p> 
  <a href="https://code.visualstudio.com/"> <img src="badges/VisualStudioCode_badge.png" height="25px" alt="VisualStudioCode_badge" /> </a>
  <a href="https://platformio.org/"> <img src="badges/PlatformIO_badge.png" height="25px" alt="PlatformIO_badge" /> </a>
  <a href="https://www.arduino.cc/"> <img src="badges/Arduino_badge.png" height="25px" alt="Arduino_badge"></a>
</p> 

## **English | [中文](./README_CN.md)**

## Version iteration:
| Version                               | Update date                       |Update description|
| :-------------------------------: | :-------------------------------: |:--------------: |
| T-CameraPlus-S3_V1.0-V1.1            | 2023-10-23                         |  Original version  |
| T-CameraPlus-S3_V1.2            | 2025-04-17                         |Improve WiFi performance, modify the microphone model, and modify the pin number to optimize the routing.    |

## PurchaseLink

| Product                     | SOC           |  FLASH  |  PSRAM   | Link                   |
| :------------------------: | :-----------: |:-------: | :---------: | :------------------: |
| T-CameraPlus-S3_V1.0-1.1   | ESP32S3 |   16M   | 8M|  [LILYGO Mall](https://www.lilygo.cc/products/t-camera-plus-s3?_pos=2&_sid=aa4cbdb34&_ss=r)  |

## Directory
- [Describe](#describe)
- [Preview](#preview)
- [Module](#module)
- [QuickStart](#quickstart)
- [PinOverview](#pinoverview)
- [RelatedTests](#RelatedTests)
- [FAQ](#faq)
- [Project](#project)

## Describe

T-CameraPlus-S3 is an intelligent camera module developed based on the ESP32S3 chip, equipped with a 240x240 TFT display, digital microphone, speaker, independent button, power control chip, SD card module, etc. It comes with a basic UI written based on LVGL, which can achieve functions such as file management, music playback, recording, and camera projection (if the factory does not write the program, you need to manually burn the UI program named "Lvgl_UI").

## Preview

### Actual Product Image

<p align="center" width="100%">
    <img src="image/12.jpg" alt="">
</p>

---

<p align="center" width="100%">
    <img src="image/13.jpg" alt="">
</p>

## Module

### 1. MCU

* Chip: ESP32-S3
* PSRAM: 8M
* FLASH: 16M
* Relevant information:
    >[Espressif](https://www.espressif.com/en/support/documents/technical-documents)

### 2. Screen

* Screen Model: fp-133h0M1d
* Size: 1.3-inch
* Resolution Ratio: 240x240px
* Screen Type: TFT
* Driver Chip: ST7789V
* Bus Communication Protocol: Standard SPI
* Dependent libraries:
    >[Arduino_GFX-1.3.7](https://github.com/moononournation/Arduino_GFX)  <br /> 
    >[lvgl-8.3.5](https://github.com/lvgl/lvgl)  <br /> 
    >[JPEGDEC-1.2.8](https://github.com/bitbank2/JPEGDEC)  <br /> 
    >[MiniTV](https://github.com/moononournation/MiniTV)  <br /> 
    >[TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)

### 3. Touch

* Chip: CST816S
* Bus Communication Protocol: IIC
* Dependent libraries:
    >[cst816t-1.5.0](https://github.com/koendv/cst816t)  <br /> 
    >[Arduino_DriveBus-1.1.16](https://github.com/Xk-w/Arduino_DriveBus)

### 4. Speaker

* Driver Chip: MAX98357A
* Bus Communication Protocol: IIS
* Others:  Default configuration is Left/2 + Right/2 channels, gain of 9dB. To change the configuration, refer to the T-CameraPlus-S3 design schematic and adjust the resistors. The selected speaker should have a maximum rated power of 3.2W, with a impedance of around 4 ohms or less than 8 ohms.
* Relevant information:
    >[MAX98357A](./information/MAX98357AETE+T.pdf)
* Dependent libraries:
    >[arduino-libhelix-0.8.1](https://github.com/pschatzmann/arduino-libhelix)  <br /> 
    >[ESP32-audioI2S-3.0.6](https://github.com/schreibfaul1/ESP32-audioI2S)

### 5. Microphone

* Driver Chip: MSM261S4030H0R
* Bus Communication Protocol: IIS
* Others:  Default configuration is right channel. To change the configuration, refer to the T-CameraPlus-S3 design schematic and adjust the resistors.

> #### T-CameraPlus-S3_V1.0-V1.1 version
> * Chip: MSM261S4030H0R
> * Bus Communication Protocol: IIS
> * Others:  Default configuration is right channel. To change the configuration, refer to the T-CameraPlus-S3 design schematic and adjust the resistors.
> * Relevant information:
>     >[MSM261S4030H0R](information/MSM261S4030H0R.pdf)
> * Dependent libraries:
>     >[DFRobot_MSM261](https://github.com/DFRobot/DFrobot_MSM261)  <br /> 
>     >[Arduino_DriveBus-1.1.16](https://github.com/Xk-w/Arduino_DriveBus)

> #### T-CameraPlus-S3_V1.2 version
> * Chip: MP34DT05-A
> * Bus Communication Protocol: PDM
> * Others:  Default configuration is right channel. To change the configuration, refer to the T-CameraPlus-S3 design schematic and adjust the resistors.
> * Relevant information:
>    >[MP34DT05-A](./information/mp34dt05-a.pdf)
> * Dependent libraries:
>    >[Arduino_DriveBus-1.1.16](https://github.com/Xk-w/Arduino_DriveBus)

### 6. Camera
* CameraModel: OV2640
* IR Filter Driver: AP1511B
* Relevant information:
    >[OV2640_Hardware_Application_V1.04](information/OV2640_Hardware_Application_V1.04.pdf)  <br /> 
    >[OV2640_Software_Application_V1.03](information/OV2640_Software_Application_V1.03.pdf)

### 7. Power Management Chip
* Chip: SY6970
* Relevant information:
>[AN_SY6970 ](information/AN_SY6970.pdf)  <br /> 
>[EVB_SY6970](information/EVB_SY6970.pdf)
* Dependent libraries:
>[XPowersLib-0.2.1](https://github.com/lewisxhe/XPowersLib)  <br /> 
>[Arduino_DriveBus-1.1.16](https://github.com/Xk-w/Arduino_DriveBus)

## QuickStart

### Examples Support

| Example | `[Platformio IDE][espressif32-v6.5.0]`<br />`[Arduino IDE][esp32_v2.0.14]`| Description | Picture |
| ------  | ------  | ------ | ------ | 
| [Wifi_Scan](./examples/Wifi_Scan) | <p align="center">![alt text][supported] |  |  |
| [Lvgl_UI](./examples/Lvgl_UI) | <p align="center">![alt text][supported] | Product factory original testing |  |
| [Wifi_Music](./examples/Wifi_Music) | <p align="center">![alt text][supported] |  |  |
| [SD_Music](./examples/SD_Music) | <p align="center">![alt text][supported] |  |  |
| [DMIC_ReadData](./examples/DMIC_ReadData) | <p align="center">![alt text][supported] |  |  |
| [SD_DMIC](./examples/SD_DMIC) | <p align="center">![alt text][supported] |  |  |
| [TFT](./examples/TFT) | <p align="center">![alt text][supported] |  |  |
| [IIC_Scan_2](./examples/IIC_Scan_2) | <p align="center">![alt text][supported] |  |  |
| [Camera_WebServer](./examples/Camera_WebServer) | <p align="center">![alt text][supported] |  |  |
| [CST816D](./examples/CST816D) | <p align="center">![alt text][supported] |  |  |
| [GFX_Test](./examples/GFX_Test) | <p align="center">![alt text][supported] |  |  |
| [SY6970](./examples/SY6970) | <p align="center">![alt text][supported] |  |  |
| [SD_MJPEG](./examples/SD_MJPEG) | <p align="center">![alt text][supported] |  |  |
| [Camera_Screen](./examples/Camera_Screen) | <p align="center">![alt text][supported] |  |  |
| [Camera_Screen_OV5640_Auto_Focus](./examples/Camera_Screen_OV5640_Auto_Focus) | <p align="center">![alt text][supported] |  |  |
| [Camera_WebServer_OV5640_Auto_Focus](./examples/Camera_WebServer_OV5640_Auto_Focus) | <p align="center">![alt text][supported] |  |  |

[supported]: https://img.shields.io/badge/-supported-green "example"

| Firmware | Description | Picture |
| ------  | ------  | ------ |
| [Lvgl_UI(V1.0-V1.1)](./firmware/[T-CameraPlus-S3_V1.0-V1.1][Lvgl_UI]_firmware_202406142310.bin) |  |  |
| [Lvgl_UI(V1.2)](./firmware/[T-CameraPlus-S3_V1.2][Lvgl_UI]_firmware_202504081446.bin) |  |  |

### PlatformIO
1. Install [VisualStudioCode](https://code.visualstudio.com/Download),Choose installation based on your system type.

2. Open the "Extension" section of the Visual Studio Code software sidebar(Alternatively, use "<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd>" to open the extension),Search for the "PlatformIO IDE" extension and download it.

3. During the installation of the extension, you can go to GitHub to download the program. You can download the main branch by clicking on the "<> Code" with green text, or you can download the program versions from the "Releases" section in the sidebar.

4. After the installation of the extension is completed, open the Explorer in the sidebar(Alternatively, use "<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>E</kbd>" go open it),Click on "Open Folder," locate the project code you just downloaded (the entire folder), and click "Add." At this point, the project files will be added to your workspace.

5. Open the "platformio.ini" file in the project folder (PlatformIO will automatically open the "platformio.ini" file corresponding to the added folder). Under the "[platformio]" section, uncomment and select the example program you want to burn (it should start with "default_envs = xxx") Then click "<kbd>[√](image/4.png)</kbd>" in the bottom left corner to compile,If the compilation is correct, connect the microcontroller to the computer and click "<kbd>[→](image/5.png)</kbd>" in the bottom left corner to download the program.

### Arduino
1. Install [Arduino](https://www.arduino.cc/en/software),Choose installation based on your system type.

2. Open the "example" directory within the project folder, select the example project folder, and open the file ending with ".ino" to open the Arduino IDE project workspace.

3. Open the "Tools" menu at the top right -> Select "Board" -> "Board Manager." Find or search for "esp32" and download the board files from the author named "Espressif Systems." Then, go back to the "Board" menu and select the development board type under "ESP32 Arduino." The selected development board type should match the one specified in the "platformio.ini" file under the [env] section with the header "board = xxx." If there is no corresponding development board, you may need to manually add the development board from the "board" directory within your project folder.

4. Open menu bar "[File](image/6.png)" -> "[Preferences](image/6.png)" ,Find "[Sketchbook location](image/7.png)"  here,copy and paste all library files and folders from the "libraries" folder in the project directory into the "libraries" folder in this directory.

5. Select the correct settings in the Tools menu, as shown in the table below.

| Setting                               | Value                                 |
| :-------------------------------: | :-------------------------------: |
| Board                                | ESP32S3 Dev Module|
| Upload Speed                     | 921600                               |
| USB Mode                           | Hardware CDC and JTAG     |
| USB CDC On Boot                | Enabled                             |
| USB Firmware MSC On Boot | Disabled                             |
| USB DFU On Boot                | Disabled                             |
| CPU Frequency                   | 240MHz (WiFi)                    |
| Flash Mode                         | QIO 80MHz                         |
| Flash Size                           | 16MB (128Mb)                     |
| Core Debug Level                | None                                 |
| Partition Scheme                | 16M Flash (3MB APP/9.9MB FATFS) |
| PSRAM                                | QSPI PSRAM                         |
| Arduino Runs On                  | Core 1                               |
| Events Run On                     | Core 1                               |

6. Select the correct port.

7. Click "<kbd>[√](image/8.png)</kbd>" in the upper right corner to compile,If the compilation is correct, connect the microcontroller to the computer,Click "<kbd>[→](image/9.png)</kbd>" in the upper right corner to download.

### firmware download
1. Open the project file "tools" and locate the ESP32 burning tool. Open it.

2. Select the correct burning chip and burning method, then click "OK." As shown in the picture, follow steps 1->2->3->4->5 to burn the program. If the burning is not successful, press and hold the "BOOT-0" button and then download and burn again.

3. Burn the file in the root directory of the project file "[firmware](./firmware/)" file,There is a description of the firmware file version inside, just choose the appropriate version to download.

<p align="center" width="100%">
    <img src="image/10.png" alt="example">
    <img src="image/11.png" alt="example">
</p>

## PinOverview

> #### T-CameraPlus-S3_V1.0-V1.1 版本
>> | lcd pins       | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | MOSI                     | IO35                  |
>> | SCLK                  | IO36                  |
>> | RST                    | IO33                  |
>> | BL                      | IO46                  |
>> | CS                    | IO34                  |
>> | DC                    | IO45                  |
>
>> | iis microphone msm261s4030h0r pins | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | BCLK                  | IO18                  |
>> | WS                  | IO39                    |
>> | DATA                  | IO40                  |
>
>> | amplifier max98357a pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | BCLK                  | IO41                  |
>> | LRCLK                  | IO42                    |
>> | DATA                  | IO38                  |
>
>> | sd pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | CS                  | IO21                  |
>> | SCLK                  | IO36                    |
>> | MOSI                  | IO35                  |
>> | MISO                  | IO37                  |
>
>> | power management ic sy6970 pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | SDA                  | IO1                  |
>> | SCL                  | IO2                    |
>> | INT                  | IO47                  |
>
>> | camera module ov2640 pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | RESET                  | IO3                  |
>> | XCLK                  | IO7                    |
>> | SIDO                  | IO1                  |
>> | SIOC                  | IO2                    |
>> | D7                  | IO6                  |
>> | D6                  | IO8                    |
>> | D5                  | IO9                  |
>> | D4                  | IO11                    |
>> | D3                  | IO13                  |
>> | D2                  | IO15                    |
>> | D1                  | IO14                  |
>> | D0                  | IO12                  |
>> | VSYNC             | IO4                  |
>> | HREF                  | IO5                  |
>> | PCLK                  | IO10                  |
>
>> | touch chip pins         | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | SDA                  | IO1                  |
>> | SCL                  | IO2                    |
>> | RST                  | IO48                  |
>> | INT                  | IO47                  |


> #### T-CameraPlus-S3_V1.2 版本
>> | lcd pins       | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | MOSI                     | IO34                  |
>> | SCLK                  | IO35                  |
>> | BL                      | IO46                  |
>> | CS                    | IO36                  |
>> | DC                    | IO45                  |
>
>> | PDM Microphone MP34DT05TR Pins | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | LRCLK                  | IO40                  |
>> | DATA                  | IO38                  |
>
>> | amplifier max98357a pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | BCLK                  | IO41                  |
>> | LRCLK                  | IO42                    |
>> | DATA                  | IO39                  |
>
>> | sd pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | CS                  | IO21                  |
>> | SCLK                  | IO35                    |
>> | MOSI                  | IO34                  |
>> | MISO                  | IO48                  |
>
>> | power management ic sy6970 pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | SDA                  | IO33                  |
>> | SCL                  | IO37                    |
>
>> | camera module ov2640 pins          | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | XCLK                  | IO7                    |
>> | SIDO                  | IO1                  |
>> | SIOC                  | IO2                    |
>> | D7                  | IO6                  |
>> | D6                  | IO8                    |
>> | D5                  | IO9                  |
>> | D4                  | IO11                    |
>> | D3                  | IO13                  |
>> | D2                  | IO15                    |
>> | D1                  | IO14                  |
>> | D0                  | IO12                  |
>> | VSYNC             | IO3                  |
>> | HREF                  | IO5                  |
>> | PCLK                  | IO10                  |
>> | PWDN                  | IO4                  |
>
>> | touch chip pins         | esp32s3 pins      |
>> | :------------------: | :------------------:|
>> | SDA                  | IO33                  |
>> | SCL                  | IO37                    |
>> | INT                  | IO47                  |

| control pin for infrared cut filter switch of camera module ov2640     | esp32s3 pins      |
| :------------------: | :------------------:|
| AP1511B_FBC                  | IO16                  |

| key1 button pins     | esp32s3 pins      |
| :------------------: | :------------------:|
| KEY1                  | IO17                  |

## RelatedTests

### Power Consumption
| firmware | program | description | picture |
| ------  | ------  | ------ | ------ | 
| [Deep_Sleep_Wake_Up]() |[Deep_Sleep_Wake_Up](./examples/Deep_Sleep_Wake_Up/)| Average current consumption: 1.7mA. For more details, please refer to the [Power Consumption Test Log](./relevant_test/PowerConsumptionTestLog_[T-CameraPlus-S3_V1.2]_20250408.pdf).| |

## FAQ

* Q. After reading the above tutorials, I still don't know how to build a programming environment. What should I do?
* A. If you still don't understand how to build an environment after reading the above tutorials, you can refer to the [LilyGo-Document](https://github.com/Xinyuan-LilyGO/LilyGo-Document) document instructions to build it.

<br />

* Q. Why does Arduino IDE prompt me to update library files when I open it? Should I update them or not?
* A. Choose not to update library files. Different versions of library files may not be mutually compatible, so it is not recommended to update library files.

<br />

* Q. Why is there no serial data output on the "Uart" interface on my board? Is it defective and unusable?
* A. The default project configuration uses the USB interface as Uart0 serial output for debugging purposes. The "Uart" interface is connected to Uart0, so it won't output any data without configuration.<br />For PlatformIO users, please open the project file "platformio.ini" and modify the option under "build_flags = xxx" from "-D ARDUINO_USB_CDC_ON_BOOT=true" to "-D ARDUINO_USB_CDC_ON_BOOT=false" to enable external "Uart" interface.<br />For Arduino users, open the "Tools" menu and select "USB CDC On Boot: Disabled" to enable the external "Uart" interface.

<br />

* Q. Why is my board continuously failing to download the program?
* A. Please hold down the "BOOT-0" button and try downloading the program again.

## Project
* [T-CameraPlus-S3_V1.0-V1.1](project/T-CameraPlus-S3_V1.0-V1.1_20241109.pdf)
* [T-CameraPlus-S3_V1.2](project/T-CameraPlus-S3_V1.2_20240417.pdf)
