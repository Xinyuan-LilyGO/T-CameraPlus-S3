<!--
 * @Description: None
 * @version: V1.0.0
 * @Author: None
 * @Date: 2023-09-22 14:37:05
 * @LastEditors: LILYGO_L
 * @LastEditTime: 2023-09-29 16:05:04
 * @License: GPL 3.0
-->
# FFJEPG

### MP3 Audio

* ffmpeg -i input.mp4 -ar 44100 -ac 1 -ab 32k -filter:a loudnorm -filter:a "volume=-5dB" output.mp3

* ffmpeg -i input.flv -ar 44100 -ac 1 -ab 44k -filter:a loudnorm -filter:a "volume=4dB" output.mp3

* ffmpeg -i input.flv -ar 44100 -ac 1 -ab 320k output.mp3

### MJPEG Video

* ffmpeg -i input.mp4 -vf "fps=60,scale=-1:240:flags=lanczos,crop=240:240" -q:v 9 output.mjpeg

* ffmpeg -i input.flv -vf "fps=60,pad=1920:1920:0:420:black,scale=-1:240:flags=lanczos" -q:v 10 -b:v 5000k output.mjpeg


