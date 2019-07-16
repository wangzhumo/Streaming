//
// Created by 王诛魔 on 2019/4/3.
//

#include "surface_sdl.h"


void show_with_surface()
{
    //window
    SDL_Window *window = NULL;
    //render
    SDL_Renderer *render = NULL;

    //init all sdl function
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Log("SDL Init.");

    //***Create Window
    //window create
    window = SDL_CreateWindow("SDL2 Window",
                              200,
                              200,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

    //window nonull
    if (!window) {
        SDL_Log("Failed to Create window!");
        goto _EXIT;
    }

    //***Create Render
    render = SDL_CreateRenderer(window, 0, 0);
    if (!render) {
        SDL_Log("Failed to Create Render!");
        goto _EXIT_WINDOW;
    }
    SDL_Log("Init Render.");

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

    //clear this render
    SDL_RenderClear(render);

    //set render to window
    SDL_RenderPresent(render);

    SDL_Delay(6000);

    _EXIT_WINDOW:
    SDL_DestroyWindow(window);

    _EXIT:
    SDL_Quit();

}