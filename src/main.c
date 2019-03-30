#include <stdio.h>
#include "ffmpeg/printf_media_info.h"
#include "ffmpeg/take_video_data.h"


int main(int argc,char *argv[]) {

    if (argc < 3){
        printf("the params count error");
        return -1;
    }
    char *input = argv[1];
    char *output = argv[2];
    if (!input || !output){
        printf("the params context error");
        return -1;
    }
    take_video(input, output);
    return 0;
}