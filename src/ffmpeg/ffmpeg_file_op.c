//
// Created by 王诛魔 on 2019/3/27.
//
#include <libavformat/avformat.h>
#include "ffmpeg_file_op.h"


int delete_file(){
    //define result
    int result;

    //file path
    result =  avpriv_io_delete("/Users/phyooos/workspace/Streaming/doc/whatever.txt");

    //do something with `result`
    if(result < 0){
        av_log(NULL,AV_LOG_ERROR,"Delete File Fail,result = [%d]",result);
    }else{
        av_log(NULL, AV_LOG_INFO, "Delete File@ Succeed");
    }

    return result;
}

int rename_file(){

    //define result
    int result;

    //file path
    result =  avpriv_io_move("/Users/phyooos/workspace/Streaming/doc/whatever.txt","/Users/phyooos/workspace/Streaming/doc/whatever_move.txt");

    //do something with `result`
    if(result < 0){
        av_log(NULL,AV_LOG_ERROR,"Move File Fail,result = [%d]",result);
    }else {
        av_log(NULL, AV_LOG_INFO, "Move File@ Succeed");
    }
    return result;
}
