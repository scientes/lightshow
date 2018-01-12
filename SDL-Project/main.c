#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#define width_glo 1600
#define height_glo 900

SDL_Renderer* wandernder_balken(SDL_Renderer* renderer, int input_signal) {
	
	SDL_SetRenderDrawColor(renderer, 150, 0, 0, 50);
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, input_signal + i, 0, input_signal + i, height_glo);
	}
	return renderer;
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
				width_glo,
				height_glo,
				SDL_WINDOW_OPENGL
				);

    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC );

    // Select the color for drawing. It is set to red here.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    int x;

        // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
    x=width_glo;
    while (x){
    //renderer=Menu(renderer,width_glo,height_glo);
		SDL_PumpEvents();
		if (state[SDL_SCANCODE_RETURN]) {
			printf("<RETURN> is pressed.\n");
		}
		if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			printf("Right and Up Keys Pressed.\n");
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		renderer = wandernder_balken(renderer, x);
		SDL_RenderPresent(renderer);
		

		x--;
	SDL_Delay(16);
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    //SDL_Delay(4000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);
    }
    SDL_Quit();
  return 0;
}

