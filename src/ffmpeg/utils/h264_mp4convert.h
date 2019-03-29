//
// Created by 王诛魔 on 2019-03-29.
//

#ifndef STREAMING_H264_MP4CONVERT_H
#define STREAMING_H264_MP4CONVERT_H

#endif //STREAMING_H264_MP4CONVERT_H

#include <libavformat/avformat.h>


void h264_mp4convert(AVFormatContext *fmt_ctx,AVPacket *in,FILE *output);