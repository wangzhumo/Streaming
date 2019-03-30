//
// Created by 王诛魔 on 2019-03-29.
// 读取h264的数据转化为MP4
//

#ifndef STREAMING_H264_MP4CONVERT_H
#define STREAMING_H264_MP4CONVERT_H

#endif //STREAMING_H264_MP4CONVERT_H

#include <libavformat/avformat.h>

int h264_mp4convert(AVFormatContext *fmt_ctx,
                    AVPacket *in,
                    FILE *output);

int alloc_and_copy(AVPacket *out_packet,
                   const uint8_t *sps_pps,
                   uint32_t sps_pps_size,
                   const uint8_t *in,
                   uint32_t in_size);

int h264_extradata_to_annexb(const uint8_t *codec_extradata,
                             const int codec_extradata_size,
                             AVPacket *out_extradata,
                             int padding);