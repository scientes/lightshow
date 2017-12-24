#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    printf("SDL_Init failed!\n");
  else
    printf("SDL_Init was successful!\n");

  SDL_Quit();
  return 0;
}

