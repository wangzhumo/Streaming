cmake_minimum_required(VERSION 3.11)
project(Streaming)

set(CMAKE_CXX_STANDARD 11)

add_executable(myffmpeg src/main.c src/sdl/first_sdl.c src/ffmpeg/ffmpeg_log.c)