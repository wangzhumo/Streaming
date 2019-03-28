//
// Created by 王诛魔 on 2019/3/28.
//

#include "printf_media_info.h"


void print_base_info(char *filePath) {
    int result;

    AVFormatContext *fmt_ctx = NULL;

    av_log_set_level(AV_LOG_INFO);

    //此方法过时,可以不调用,但是为了兼容,还是加入
    av_register_all();

    //&fmt_ctx 传入指针的地址,让avformat_open_input为我们分配一个AVFormatContext
    //filePath 文件的地址,一般会根据地址的后缀名来做响应的解析
    //NULL     解析文件的格式,如果不传则根据 filePath的后缀来解析
    //NULL     可选操作
    result = avformat_open_input(&fmt_ctx, filePath, NULL, NULL);

    if (result < 0) {
        av_log(NULL, AV_LOG_ERROR, "Can't Open File: %s\n", av_err2str(result));
        goto __OPEN_ERROR;
    }

    //成功打开了文件
    //fmt_ctx  传入上下文
    //0        流的索引值,一般 0 即可
    //filePath 输入文件名字
    //0        是否输入0  输入1
    av_dump_format(fmt_ctx, 0, filePath, 0);

    //此时我们关闭这个输入
    avformat_close_input(&fmt_ctx);

    __OPEN_ERROR:
    av_free(fmt_ctx);

}