#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Renderer* effect_wandernder_balken(SDL_Renderer* renderer, int input_signal) {

	SDL_SetRenderDrawColor(renderer, 150, 0, 0, 50);
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, input_signal + i, 0, input_signal + i, height_glo);
	}
	return renderer;
}
SDL_Renderer* wandernder_balken(SDL_Renderer* renderer, int input_signal) {

return renderer;
}

#endif // EFFECT_H_INCLUDED
