CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

SET(CMAKE_CXX_STANDARD 11)

PROJECT(Streaming C)

INCLUDE_DIRECTORIES(./include/)

LINK_DIRECTORIES(./lib/)

SET(SOURCE_FILES ./src/main.c)

ADD_EXECUTABLE(Streaming ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(
        Streaming
        avcodec
        avdevice
        avfilter
        avformat
        avresample
        avutil
        postproc
        swresample
        swscale
)
