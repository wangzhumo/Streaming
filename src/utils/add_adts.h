//
// Created by 王诛魔 on 2019/3/29.
//

#ifndef STREAMING_ADD_ADTS_H
#define STREAMING_ADD_ADTS_H

#endif //STREAMING_ADD_ADTS_H



#include <stdio.h>
#include "libavutil/log.h"
#include "libavformat/avio.h"
#include "libavformat/avformat.h"


void adts_header(char *szAdtsHeader, int dataLen);
