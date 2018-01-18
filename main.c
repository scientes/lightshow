#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define WIDTH_GLOBAL 1600
#define HEIGHT_GLOBAL 900
#define FPS_CAP 60
#include "effect.h"
#include <time.h>
#include <sys/time.h>

unsigned long long milissinceepoch(){


    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 +(unsigned long long)(tv.tv_usec) / 1000;
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
    //atexit(SDL_Quit);
    window = SDL_CreateWindow("lightshow",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,

				WIDTH_GLOBAL,
				HEIGHT_GLOBAL,
				SDL_WINDOW_OPENGL
				);

    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    // We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC );

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int x;

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	x=1;
	int t=0;
	int frames=0;
	unsigned long long rendertime=0;
	unsigned long long start;
	unsigned long long stop;
	unsigned long long time;
	int u;
	SDL_SetRenderDrawBlendMode(renderer,1);
    while (x){
        start=milissinceepoch();
		x++;
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		u+=1;
		if (t<0){
            t=WIDTH_GLOBAL;
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			//printf("<RETURN> is pressed.\n");
			t+=2;
		}
		if (state[SDL_SCANCODE_LEFT]) {
			//printf("<RETURN> is pressed.\n");
			t-=2;
			}
		if (state[SDL_SCANCODE_RETURN]) {
			//printf("Right and Up Keys Pressed.\n");
			SDL_SetRenderDrawColor(renderer,200,0,0,255);
			effect_rand_points(renderer,x%10,50);}

		if (state[SDL_SCANCODE_4]){             //Caspar Hello world linie
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            effect_linieausprobieren(renderer, 1);
		}


        SDL_SetRenderDrawColor(renderer,0,0,255,255);

        //effect_func_test_dummy(renderer,u*0.01,0,0);
        effect_func_quad(renderer,log(u*0.01),800,0);
        //effect_func_sin(renderer,u*0.01,0.5,800,450);


        //SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer,100,100,100,200);
        effect_coord(renderer);

        SDL_SetRenderDrawColor(renderer,0,255,0,255);
        effect_wandernder_balken(renderer, t);
        SDL_RenderPresent(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		if (x%10==0){
            if(event.type==256){
            printf("%Beendung durch X\n");
            x=0;
            }}
		if (state[SDL_SCANCODE_ESCAPE]){
            printf("ESC pressed.Aborting\n");
            x=0;
		}
		frames++;
		stop=milissinceepoch();
		time=stop-start;
		rendertime+=time;
		if (frames%FPS_CAP){
            printf("Avarage rendertime in ms: %d\n",rendertime/frames);
		}
    if (time<(1000/FPS_CAP)){
        SDL_Delay((1000/FPS_CAP)-time);
    }
    }
    SDL_DestroyWindow(window);
    }
    SDL_Quit();
  return 0;
}

