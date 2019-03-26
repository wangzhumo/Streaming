//
// Created by 王诛魔 on 2019/3/27.
//
#include <stdio.h>
#include <libavutil/log.h>
#include "ff_log.h"

void printf_ffmpeg_log(){
    av_log_set_level(AV_LOG_DEBUG);

    av_log(NULL,AV_LOG_INFO,"Hello World! \n");
}