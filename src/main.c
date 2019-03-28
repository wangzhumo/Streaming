#include <stdio.h>
#include "ffmpeg/take_audio_data.h"
#include "ffmpeg/printf_media_info.h"


int main(int argc,char *argv[]) {

    if (argc < 3){
        printf("the params count error");
        return -1;
    }
    char *input = argv[1];
    char *output = argv[2];
    print_base_info(input);
    if (!input || !output){
        printf("the params context error");
        return -1;
    }
    return take_audio(input, output);
}