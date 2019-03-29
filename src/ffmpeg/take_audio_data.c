//
// Created by 王诛魔 on 2019/3/29.
//

#include <stdio.h>
#include "take_audio_data.h"
#include "utils/add_adts.h"

int take_audio(char *res,char *out)
{
    int result;
    int audio_index;
    int lenght;

    AVFormatContext *fmt_ctx = NULL;
    AVPacket packet;

    av_log_set_level(AV_LOG_INFO);

    //1. res , open input file,create output file
    result = avformat_open_input(&fmt_ctx, res, NULL, NULL);

    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't Open File: %s\n", av_err2str(result));
        return -1;
    }

    FILE *out_file = fopen(out, "wb");
    if (!out_file){
        av_log(NULL, AV_LOG_ERROR, "Can't Create File : %s\n",out);
        //PS:一定记得关闭这个流
        avformat_close_input(&fmt_ctx);
        return -1;
    }


    //2.get stream ,read stream
    //fmt_ctx      操作对象
    //AVMEDIA_TYPE_AUDIO    需要操作的流是音频流
    //-1           要处理的流的索引号
    //-1           相关的流索引号,比如是你要处理音频流对应的视频流
    //0            对应的编解码器
    result = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);

    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't Find Best Stream\n");
        //关闭输入流
        avformat_close_input(&fmt_ctx);
        //关闭输出流文件
        fclose(out_file);
        return -1;
    }

    //初始化 AVPacket
    av_init_packet(&packet);

    audio_index = result;

    //3.write to output file
    while (av_read_frame(fmt_ctx, &packet) >= 0){
        if (packet.stream_index == audio_index){
            //创建ADTS头
            char adts_header_buff[7];
            adts_header(adts_header_buff,packet.size);
            //写入ADTS头
            fwrite(adts_header_buff, 1, 7, out_file);
            lenght = fwrite(packet.data, 1, packet.size, out_file);
            if (lenght != packet.size){
                //长度不一致,是否退出看业务流程是怎么样的
                av_log(NULL, AV_LOG_WARNING, "Waning , write length is not equals data size");
            }
        }
        av_packet_unref(&packet);
    }

    //4.release res
    av_log(NULL,AV_LOG_INFO,"Take Audio Success,File : %s\n",out);
    avformat_close_input(&fmt_ctx);
    if (out_file){
        fclose(out_file);
    }
    return 0;
}