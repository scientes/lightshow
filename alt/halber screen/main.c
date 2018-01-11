#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define width 1600
#define height 900

int Menu(SDL_Renderer* renderer,width,height){
    SDL_SetRenderDrawColor(renderer,153,153,102,50);
    for (int i=0;i>height/2;i++){
        SDL_RenderDrawLine(renderer,width/2-width/4,height/4+i,width/2+width/4,height/4+i)

    }


}






int main(int argc, char* args[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init failed!\n");
        }
    else{
        printf("SDL_Init was successful!\n");
    SDL_Window* window = SDL_CreateWindow("lightshow",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				width,
				height,
				SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN_DESKTOP
				);
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    int x;

        // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    While x{
    Menu()
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(4000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);
    }
    SDL_Quit();
  return 0;
}

