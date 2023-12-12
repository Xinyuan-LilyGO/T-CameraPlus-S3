<!--
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-09-22 14:37:05
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-22 15:20:33
 * @License: GPL 3.0
-->
### MJPEG Video

#### 240x240@30fps

```copy
ffmpeg -i input.flv -vf "fps=60,scale=-1:240:flags=lanczos,crop=240:240" -q:v 9 240_30fps.mjpeg
```

```copy
ffmpeg -i input.mp4 -vf "fps=60,scale=-1:240:flags=lanczos,crop=240:240" -q:v 9 240_30fps.mjpeg
```
