###FFmpeg常用命令分类

#### 基本查询命令

| 命令         |                                            |
| ------------ | ------------------------------------------ |
| -version     | 版本                                       |
| -demuxers    | 可以使用的解封装  分解                     |
| -muxers      | 可以使用的复用      复用                   |
| -devices     | 输入设备                                   |
| -codecs      | 所有的编码/解码器                          |
| -decoders    | 可用解码器                                 |
| -encoders    | 可用编码器                                 |
| -bsfs        | 显示可用的比特流filter  (对比特流进行处理) |
| -formats     | 显示可用的格式                             |
| -protocols   | 输入文件的协议查询(rtmp等等)               |
| -filters     | 所有可用的fiter                            |
| -pix_fmts    | 像素格式  rgb  yuv                         |
| -sample_fmts | 采样格式(位数 float)                       |
| -layouts     | 显示channel名称                            |
| -colors      | 显示支持的颜色                             |



#### 录制命令

##### 录制MAC屏幕

`ffmpeg -f avfoundation -i 1 -r 30  /Users/phyooos/media/201903261211.yuv  `

- `-f`  指定采集数据
- `-i`  指定了输入源   `1` 是输入的索引
- `-r`  帧率



*播放*

`ffplay -s 2560x1600 -pix_fmt uyvy422 ~/media/201903261211.yuv`



*设备列表*

`ffmpeg -f avfoundation -list_devices true -i ""`

```shell
# phyooos @ wangzhumo in ~/media [0:19:02] C:1
$ ffmpeg -f avfoundation -list_devices true -i ""
[AVFoundation input device @ 0x7fc8b1c01300] AVFoundation video devices:
[AVFoundation input device @ 0x7fc8b1c01300] [0] FaceTime HD Camera
[AVFoundation input device @ 0x7fc8b1c01300] [1] Capture screen 0
[AVFoundation input device @ 0x7fc8b1c01300] [2] Capture screen 1
[AVFoundation input device @ 0x7fc8b1c01300] AVFoundation audio devices:
[AVFoundation input device @ 0x7fc8b1c01300] [0] MDR-XB950N1
[AVFoundation input device @ 0x7fc8b1c01300] [1] Built-in Microphone
```



##### MAC录制音频

`ffmpeg -f avfoundation -i :0 /Users/phyooos/media/201903261222.wav`

- :1 代表了音频设备 (内置麦克风)



##### MAC录屏 + 声音

`ffmpeg -f avfoundation -i 1:1 -r 30 -c:v libx264 -crf 0 -c:a libfdk_aac -profile:a aac_he_v2 -b:a 32k ~/media/201903261237.flv`

由于本机没有`libfdk_aac`

```shell
# phyooos @ wangzhumo in ~/media [0:43:28]
$ ffmpeg -encoders | grep "aac"

A..... aac                  AAC (Advanced Audio Coding)
A....D aac_at               aac (AudioToolbox) (codec aac)


```







#### 分解与复用


#### 处理原始数据

#### 裁剪与合并

#### 图片/视屏互转

#### 直播命令相关

#### 滤镜

