#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Renderer* effect_wandernder_balken(SDL_Renderer* renderer, int input_signal) {
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, input_signal + i, 0, input_signal + i, height_glo);
	}
	return renderer;
}
SDL_Renderer* effect_dummy(SDL_Renderer* renderer, int input_signal) {

return renderer;
}
SDL_Renderer* effect_enlarge_array(SDL_Renderer* renderer, int* pixel_array_width,int* pixel_array_height) {
    for (int i=0;i<(sizeof(pixel_array_height)/sizeof(int));i++){
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i]+1,pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]+1);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i]-1,pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]-1);
    }
return renderer;
}

SDL_Renderer* effect_array(SDL_Renderer* renderer, int* pixel_array_width,int* pixel_array_height ) {
    //printf("%d %d\n",sizeof(pixel_array_height)/sizeof(int),sizeof(pixel_array_width)/sizeof(int));
    for (int i=0;i<(sizeof(pixel_array_height)/sizeof(int));i++){
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]);
    //printf("%d %d\n",pixel_array_width[i],pixel_array_height[i]);
    }

return renderer;
}
SDL_Renderer* effect_rand_points(SDL_Renderer* renderer, int input_signal,int num_points) {
    int i;

    int width;
    int height;


    for( i = 0 ; i < num_points ; i++ ) {
        width=rand() % width_glo;
        height=rand() % height_glo;
        SDL_RenderDrawPoint(renderer,width,height);
        SDL_RenderDrawPoint(renderer,width+1,height);
        SDL_RenderDrawPoint(renderer,width+1,height+1);
        SDL_RenderDrawPoint(renderer,width,height+1);
        SDL_RenderDrawPoint(renderer,width-1,height-1);
        SDL_RenderDrawPoint(renderer,width,height-1);
        SDL_RenderDrawPoint(renderer,width+1,height-1);
        SDL_RenderDrawPoint(renderer,width-1,height+1);
        SDL_RenderDrawPoint(renderer,width-1,height);


        }
    //renderer=effect_enlarge_array(renderer,width,height);
return renderer;
}


#endif // EFFECT_H_INCLUDED
