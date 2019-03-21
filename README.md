# Streaming

## SDL

*SDL(Simple DirectMedia Layer)是一套开源的多媒体开发库,主要提供了控制图像,声音输出和输入的函数.* 

#### 第一次接触

```
clang -g -o firstsdl first_sdl.c `pkg-config --cflags --libs sdl2`
```


--libs 参数获取库的地址

```shell
# phyooos @ wangzhumo in ~ [0:54:13] C:1
$ pkg-config --libs sdl2
-L/usr/local/lib -lSDL2
```

--cflags 获取了相关的头文件

```shell
# phyooos @ wangzhumo in ~ [0:59:57]
$ pkg-config --cflags sdl2
-D_THREAD_SAFE -I/usr/local/include/SDL2
```

