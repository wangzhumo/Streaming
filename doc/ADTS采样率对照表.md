### ADTS头对照表



#### **syncword** ：同步头

> 总是0xFFF, all bits must be 1，代表着一个ADTS帧的开始



#### **ID**：MPEG Version

> 0 for MPEG-4, 1 for MPEG-2



#### **Layer**：always: '00'



#### **profile**：表示使用哪个级别的AAC



#### **sampling_frequency_index**

- 0: 96000 Hz
- 1: 88200 Hz
- 2: 64000 Hz
- 3: 48000 Hz
- 4: 44100 Hz
- 5: 32000 Hz
- 6: 24000 Hz
- 7: 22050 Hz
- 8: 16000 Hz
- 9: 12000 Hz
- 10: 11025 Hz
- 11: 8000 Hz
- 12: 7350 Hz
- 13: Reserved
- 14: Reserved
- 15: frequency is written explictly



#### channel_configuration 声道数 

- 0: Defined in AOT Specifc Config
- 1: 1 channel: front-center
- 2: 2 channels: front-left, front-right
- 3: 3 channels: front-center, front-left, front-right
- 4: 4 channels: front-center, front-left, front-right, back-center
- 5: 5 channels: front-center, front-left, front-right, back-left, back-right
- 6: 6 channels: front-center, front-left, front-right, back-left, back-right, LFE-channel
- 7: 8 channels: front-center, front-left, front-right, side-left, side-right, back-left, back-right, LFE-channel
- 8-15: Reserved



#### **frame_length** 

> 一个ADTS帧的长度包括ADTS头和AAC原始流

#### **adts_buffer_fullness**

>  0x7FF 说明是码率可变的码流





