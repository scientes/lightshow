#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define width_glo 1600
#define height_glo 900
#include "effect.h"
#include <time.h>

int milissinceepoch(){
    #include <sys/time.h>

    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch =
    (unsigned long long)(tv.tv_sec) * 1000 +(unsigned long long)(tv.tv_usec) / 1000;
    return millisecondsSinceEpoch;

}

int main(int argc, char* args[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init failed!\n");
        }
    else{
        printf("SDL_Init was successful!\n");
    atexit(SDL_Quit);
    window = SDL_CreateWindow("lightshow",
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
	x=1;
	int t=0;


    printf("%llu\n", milissinceepoch());
    while (x){
		x++;
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		if (t<0){
            t=width_glo;
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			printf("<RETURN> is pressed.\n");
			t+=5;
		}
		if (state[SDL_SCANCODE_LEFT]) {
			printf("<RETURN> is pressed.\n");
			t-=5;
		}
		if (state[SDL_SCANCODE_RETURN]) {
			printf("Right and Up Keys Pressed.\n");
			SDL_SetRenderDrawColor(renderer,200,0,0,50);
			renderer=effect_rand_points(renderer,x%10,50);}


        SDL_SetRenderDrawColor(renderer,0,50,0,0);
        renderer = effect_wandernder_balken(renderer, t);
        SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		if (x%10==0){
            if(event.type==256){
            printf("%d\n",event.type);
            x=0;
            }}
		if (state[SDL_SCANCODE_ESCAPE]){
            printf("ESC pressed.Aborting\n");
            x=0;
		}

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

