//
// Created by 王诛魔 on 2019-03-29.
// 获取视频文件中的h264并输出到mp4
//

#include "take_video_data.h"
#include "utils/h264_mp4convert.h"


int take_video(char *input, char *out) {
    int error;
    char errors[1024];

    int stream_index = -1;

    AVFormatContext *fmt_ctx = NULL;
    AVPacket packet;

    av_log_set_level(AV_LOG_INFO);

    //1. res , open input file,create output file
    error = avformat_open_input(&fmt_ctx, input, NULL, NULL);

    if (error < 0) {
        av_strerror(error, errors,1024);
        av_log(NULL, AV_LOG_ERROR, "Can't Open File: %s, %d(%s)\n", input, error, errors);
        return -1;
    }

    FILE *out_file = fopen(out, "wb");
    if (!out_file) {
        av_log(NULL, AV_LOG_ERROR, "Can't Create File : %s\n", out);
        //PS:一定记得关闭这个流
        avformat_close_input(&fmt_ctx);
        return -1;
    }

    //打印文件信息
    av_dump_format(fmt_ctx, 0, input, 0);

    //数据包
    av_init_packet(&packet);
    packet.data = NULL;
    packet.size = 0;

    //2.find best stream
    stream_index = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);

    if (stream_index < 0) {
        av_log(NULL, AV_LOG_DEBUG, "Can't Find %s Best Stream In file %s\n",
               av_get_media_type_string(AVMEDIA_TYPE_VIDEO), input);
        return AVERROR(EINVAL);
    }

    //3.read packet ,write to file
    while (av_read_frame(fmt_ctx, &packet) >= 0) {
        if (packet.stream_index == stream_index) {
            //读取,操作并写到输入文件
            h264_mp4convert(fmt_ctx, &packet, out_file);
        }
        av_packet_unref(&packet);
    }
    //4.完成写入后,关闭输入,关闭输出文件
    avformat_close_input(&fmt_ctx);
    if (out_file) {
        fclose(out_file);
    }
    return 0;
}