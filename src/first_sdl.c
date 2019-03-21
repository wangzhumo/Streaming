#include <SDL.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
  SDL_Window *window = NULL; 

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("SDL2 Window",
      200,
      200,
      640,
      480,
      SDL_WINDOW_SHOWN);

  //window nonull 
  if(!window)
  {
    printf("Failed to Create window!");
    goto _EXIT;
  }
  
  SDL_DestroyWindow(window);
  
_EXIT:
  SDL_Quit();
  
  return 0;
}
