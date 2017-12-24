#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

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
				1600,
				900,
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


        // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    for(int i=0;900>i;i++){
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 0);
    SDL_RenderDrawLine(renderer,0,0i,1600,i);
    SDL_RenderPresent(renderer);

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(2);
    }

    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(4000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);
    }
    SDL_Quit();
  return 0;
}
