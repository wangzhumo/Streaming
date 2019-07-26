#Cmake Version
cmake_minimum_required(VERSION 3.11)

#C++ build
set(CMAKE_CXX_STANDARD 11)

#project name
project(streaming)

# Add the 'Modules' folder to the search path for FindXXX.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

aux_source_directory(src SOURCE_FILES)


find_package(SDL2 REQUIRED)

include_directories(
        include
        ${SDL2_INCLUDE_DIR})

#SET(SOURCE_FILES
#        src/main.c
#        src/ffmpeg/ff_log.c src/ffmpeg/ff_log.h
#        src/ffmpeg/ffmpeg_file_op.c src/ffmpeg/ffmpeg_file_op.h
#        src/ffmpeg/list_file.c src/ffmpeg/list_file.h
#        src/ffmpeg/printf_media_info.c src/ffmpeg/printf_media_info.h
#        src/ffmpeg/take_audio_data.c src/ffmpeg/take_audio_data.h
#        src/ffmpeg/take_video_data.c src/ffmpeg/take_video_data.h
#        src/ffmpeg/utils/h264_mp4convert.c src/ffmpeg/utils/h264_mp4convert.h
#        src/ffmpeg/utils/add_adts.c src/ffmpeg/utils/add_adts.h
#        src/play/sample_play_video.c src/play/sample_play_video.h
#        src/sdl/surface_sdl.c src/sdl/surface_sdl.h)

add_executable(Streaming ${SOURCE_FILES})

link_directories(
        lib
)

target_link_libraries(
        Streaming
        ${SDL2_LIBRARY}
)
