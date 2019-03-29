CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

SET(CMAKE_CXX_STANDARD 11)

PROJECT(Streaming C)

INCLUDE_DIRECTORIES(./include/)

LINK_DIRECTORIES(./lib/)

SET(SOURCE_FILES
        src/main.c
        src/ffmpeg/ff_log.c src/ffmpeg/ff_log.h
        src/ffmpeg/ffmpeg_file_op.c src/ffmpeg/ffmpeg_file_op.h
        src/ffmpeg/list_file.c src/ffmpeg/list_file.h
        src/ffmpeg/printf_media_info.c src/ffmpeg/printf_media_info.h
        src/ffmpeg/take_audio_data.c src/ffmpeg/take_audio_data.h
        src/ffmpeg/utils/add_adts.c src/ffmpeg/utils/add_adts.h)

ADD_EXECUTABLE(Streaming ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(
        Streaming
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
)
