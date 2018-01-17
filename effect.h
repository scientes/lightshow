#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>

/**
 * Gibt zu einem Paar mathematischer x- und y-Koordinaten
 * die BMP X- und Y-Koordinaten aus.
 *
 * x - Wert zwischen x_MIN und x_MAX.
 * y - Wert zwischen y_MIN und y_MAX.
 * X - Berechneter BMP Wert zwischen 0 und width_glo.
 * Y - Berechneter BMP Wert zwischen 0 und height_glo.
 */
void toBMP(double x, double y, int* X, int* Y,int x_MIN,int x_MAX, int y_MIN, int y_MAX) {
  if ((x < x_MIN) || (x > x_MAX) || (y < y_MIN) || (y > y_MAX)) {
    *X = 0;
    *Y = 0;
    return;
  }
  *X = (int) ((x - x_MIN) * width_glo / (x_MAX - x_MIN));
  *Y = height_glo - (int) ((y - y_MIN) * height_glo / (y_MAX - y_MIN));
}


/**
 * Gibt zu einem Paar BMP X- und Y-Koordinaten
 * die mathematischen x- und y-Koordinaten aus.
 *
 * X - Wert zwischen 0 und width_glo.
 * Y - Wert zwischen 0 und height_glo.
 * x - Berechnete mathematische Koordinate zwischen x_MIN und x_MAX.
 * y - Berechnete mathematische Koordinate zwischen y_MIN und y_MAX.
 */
void toMath(int X, int Y, double* x, double* y,int x_MIN,int x_MAX, int y_MIN, int y_MAX) {
  if ((X < 0) || (X > width_glo) || (Y < 0) || (Y > height_glo)) {
    *x = x_MIN;
    *y = y_MIN;
    return;
  }
  *x = x_MIN + ((double) X * (x_MAX - x_MIN)) / width_glo;
  *y = y_MIN + ((double) (height_glo - Y) * (y_MAX - y_MIN)) / height_glo;
}

void effect_wandernder_balken(SDL_Renderer* renderer, int input_signal) {
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, input_signal + i, 0, input_signal + i, height_glo);
	}
}
void effect_dummy(SDL_Renderer* renderer, int input_signal) {

}
void effect_enlarge_array(SDL_Renderer* renderer, int* pixel_array_width,int* pixel_array_height) {
    for (int i=0;i<(sizeof(pixel_array_height)/sizeof(int));i++){
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i]+1,pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]+1);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i]-1,pixel_array_height[i]);
    SDL_RenderDrawPoint(renderer,pixel_array_width[i],pixel_array_height[i]-1);
    }
}

void effect_array(SDL_Renderer* renderer, char* pixel_array ) {
    for(int y=0;y<height_glo;y++){
        for(int x=0;x<width_glo;x++){
        if (pixel_array[y*width_glo+x]==1){
        SDL_RenderDrawPoint(renderer,x,y);
        }
        }
        }

}
void effect_rand_points(SDL_Renderer* renderer, int input_signal,int num_points) {
    int i;
    int width;
    int height;
    srand(input_signal);
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
    }

void effect_func_test_dummy(SDL_Renderer* renderer, float radius, int x, int y){
    char *screen;
    int X,Y;
    screen=malloc(height_glo*width_glo*sizeof(char));
    int XX, YY;

    toBMP(0.0, 0.0, &XX, &YY,-16,16,-9,9);
    for (int X = 0; X < width_glo; X++) {
        screen[YY * width_glo + X] = 1;
        }
    for (int Y = 0; Y < height_glo; Y++) {
        screen[Y * width_glo + XX] = 1;
        }
    for (int X = 0; X < width_glo; X++) {
    double x,y;

    toMath(X, 0, &x, &y,-16,16,-9,9);          // Nur x interessiert
    toBMP(x, x, &XX, &YY,-16,16,-9,9);
    screen[YY*width_glo+X]=1;
    }
    effect_array(renderer,screen);
    free(screen);





}

#endif // EFFECT_H_INCLUDED
