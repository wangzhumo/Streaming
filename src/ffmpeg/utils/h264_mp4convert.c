//
// Created by 王诛魔 on 2019-03-29.
//

#include "h264_mp4convert.h"

#ifndef AV_WB32
#define AV_WB32(p, val) do {            \
uint32_t d = (val);                     \
((uint8_t*)(p))[3] = (d);               \
((uint8_t*)(p))[2] = (d) >> 8;          \
((uint8_t*)(p))[1] = (d) >> 16;         \
((uint8_t*)(p))[0] = (d) >> 24;         \
}while(0)
#endif

#ifndef AV_RB16
#define AV_RB16(x)((((const uint8_t*)(x))[0] << 8) |((const uint8_t*)(x))[1])
#endif


//增加特征码
//SPS/PPS数据是4个字节  00 00 00 01
//非SPS/PPS 是3个字节
int alloc_and_copy(AVPacket *out_packet,
                   const uint8_t *sps_pps, uint32_t sps_pps_size,
                   const uint8_t *in, uint32_t in_size) {

    uint32_t offset = out_packet->size;
    //out_packet中的offset 如果有数据则不是 SPS/PPS 所以,字节数是不一样的
    uint8_t nal_header_size = offset ? 3 : 4;

    int error_code;

    //对输出的out_packet进行扩容
    //扩容 = SPS/PPS 的长度  + NAL头数据的长度  + 数据本身的长度
    error_code = av_grow_packet(out_packet, sps_pps_size + nal_header_size + in_size);
    if (error_code < 0) {
        return error_code;
    }

    //将SPS/PPS数据写入
    if (sps_pps) {
        //首先把 sps_pps 拷贝到 out_packet 中
        memcpy(out_packet->data + offset, sps_pps, sps_pps_size);
        //之后移动到offset + sps_pps_size + nal_header_size,写入数据in
        memcpy(out_packet->data + offset + sps_pps_size + nal_header_size, in, in_size);
    }
    if (!offset) {
        AV_WB32(out_packet->data + sps_pps_size, 1);
    } else {
        (out_packet->data + offset + sps_pps_size)[0] = 0;
        (out_packet->data + offset + sps_pps_size)[1] = 0;
        (out_packet->data + offset + sps_pps_size)[2] = 1;
    }
    return 0;
}

//读取扩展数据,PPS/SPS
int h264_extradata_to_annexb(const uint8_t *codec_extradata,
                             const int codec_extradata_size,
                             AVPacket *out_extradata,
                             int padding) {
    uint16_t unit_size;
    uint64_t total_size = 0;
    uint8_t *out = NULL, unit_nb, sps_done = 0, sps_seen = 0,
            pps_seen = 0, sps_offset = 0, pps_offset = 0;

    //扩展数据的前四个无用,直接跳过即可
    const uint8_t *extradata = codec_extradata + 4;
    static const uint8_t nalu_header[4] = {0, 0, 0, 1};
    int length_size = (*extradata++ & 0x3) + 1;
    //retrieve length coded size 用于指示编码数据长度所需字节数

    sps_offset = pps_offset = -1;

    /* retrieve sps and pps unit(s) */
    unit_nb = *extradata++ & 0x1f; /* number of sps unit(s) */
    if (!unit_nb) {
        goto pps;
    } else {
        sps_offset = 0;
        sps_seen = 1;
    }

    while (unit_nb--) {
        int err;

        unit_size = AV_RB16(extradata);
        total_size += unit_size + 4;
        if (total_size > INT_MAX - padding) {
            av_log(NULL, AV_LOG_ERROR,
                   "Too big extradata size, corrupted stream or invalid MP4/AVCC bitstream\n");
            av_free(out);
            return AVERROR(EINVAL);
        }
        if (extradata + 2 + unit_size > codec_extradata + codec_extradata_size) {
            av_log(NULL, AV_LOG_ERROR, "Packet header is not contained in global extradata, "
                                       "corrupted stream or invalid MP4/AVCC bitstream\n");
            av_free(out);
            return AVERROR(EINVAL);
        }
        if ((err = av_reallocp(&out, total_size + padding)) < 0)
            return err;
        memcpy(out + total_size - unit_size - 4, nalu_header, 4);
        memcpy(out + total_size - unit_size, extradata + 2, unit_size);
        extradata += 2 + unit_size;
        pps:
        if (!unit_nb && !sps_done++) {
            unit_nb = *extradata++; /* number of pps unit(s) */
            if (unit_nb) {
                pps_offset = total_size;
                pps_seen = 1;
            }
        }
    }

    if (out)
        memset(out + total_size, 0, padding);

    if (!sps_seen)
        av_log(NULL, AV_LOG_WARNING,
               "Warning: SPS NALU missing or invalid. "
               "The resulting stream may not play.\n");

    if (!pps_seen)
        av_log(NULL, AV_LOG_WARNING,
               "Warning: PPS NALU missing or invalid. "
               "The resulting stream may not play.\n");

    out_extradata->data = out;
    out_extradata->size = total_size;

    return length_size;
}

int h264_mp4convert(AVFormatContext *fmt_ctx, AVPacket *in, FILE *output) {

    AVPacket *out = NULL;
    AVPacket sps_pps_pkt;

    int length;

    uint8_t unit_type;
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
    //数据 data + size 指向数据的大小长度的位置上
    buf_end = in->data + in->size;

    //此处的in->data + in->size 实际上是,in中的data位置移动了in->size位置的距离
    //使得 in->data 此时指向了它的最尾部
    do {
        result = AVERROR(EINVAL);
        if (buf + 4 > buf_end) {
            goto __FAIL;
        }
        //packet中前4字节保存的是这个packet中的帧数量
        for (nal_size = 0, i = 0; i < 4; i++) {
            //这里拿到了size的大小
            nal_size = (nal_size << 8) | buf[i];
        }
        //此时后移4个字节,跳过帧数量的部分,来到真正的帧数据
        buf += 4;
        //NAL Header 占用了一个字节
        unit_type = *buf & 0x1f;

        //判断数据合法性
        if (nal_size > buf_end - buf || nal_size < 0) {
            goto __FAIL;
        }

        //判断这个帧是不是关键帧  5 关键帧  7 SPS  8 PPS
        if (unit_type == 5) {
            //如果是关键帧
            h264_extradata_to_annexb(
                    fmt_ctx->streams[in->stream_index]->codec->extradata,
                    fmt_ctx->streams[in->stream_index]->codec->extradata_size,
                    &sps_pps_pkt,
                    AV_INPUT_BUFFER_PADDING_SIZE);
            if ((result = alloc_and_copy(out, sps_pps_pkt.data, sps_pps_pkt.size, buf, nal_size)) < 0) {
                goto __FAIL;
            }
        } else {
            if ((result = alloc_and_copy(out, NULL, 0, buf, nal_size)) < 0) {
                goto __FAIL;
            }
        }

        length = fwrite(out->data, 1, out->size, output);
        if (length != out->size) {
            //如果写入长度和实际数据长度不符合,则失败
            av_log(NULL, AV_LOG_WARNING, "Warning,Length of writed data != packet.size(%d,%d)\n",
                   length, out->size);
        }
        //写入成功,把缓冲数据写入File
        fflush(output);

        __NEXT_NAL:
        buf += nal_size;
        cumul_size += nal_size + 4;
    } while (cumul_size < buf_size);

    __FAIL:
    av_packet_free(&out);
    return result;
}