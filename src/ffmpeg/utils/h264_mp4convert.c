//
// Created by 王诛魔 on 2019-03-29.
//

#include "h264_mp4convert.h"


void h264_mp4convert(AVFormatContext *fmt_ctx, AVPacket *in, FILE *output) {

    AVPacket *out = NULL;
    AVPacket sps_pps_pkt;

    int length;

    uint8_t uint_type;
    int32_t nal_size;
    uint32_t cumul_size = 0;

    const uint8_t *buf;
    const uint8_t *buf_end;
    int buf_size;
    int result = 0, i;

    out = av_packet_alloc();

    //packet中的真实数据
    buf = in->data;
    //数据的size
    buf_size = in->size;
    //数据 data + size 指向数据的大小
    buf_end = in->data + in->size;

    //此处的in->data + in->size 实际上是,in中的data位置移动了in->size的数据位数
    //使得 in->data 此时指向了它的最尾部
    do {
        result = AVERROR(EINVAL);
        if (buf + 4 > buf_end) {
            goto __FAIL;
        }
        for (nal_size = 0, i = 0; i < 4; i++) {
            nal_size = (nal_size << 8) | buf[i];

        }
    }

    __FAIL:
}