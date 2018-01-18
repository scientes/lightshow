#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
int WIDTH_GLOBAL,HEIGHT_GLOBAL,FPS_CAP;
/**
 * Gibt zu einem Paar mathematischer x- und y-Koordinaten
 * die BMP X- und Y-Koordinaten aus.
 *
 * x - Wert zwischen x_MIN und x_MAX.
 * y - Wert zwischen y_MIN und y_MAX.
 * X - Berechneter BMP Wert zwischen 0 und WIDTH_GLOBAL.
 * Y - Berechneter BMP Wert zwischen 0 und HEIGHT_GLOBAL.
 */
struct function_start_time{
    char functionid;
    unsigned long long starttime;
};
void toBMP(double x, double y, int* X, int* Y,int x_MIN,int x_MAX, int y_MIN, int y_MAX) {
  if ((x < x_MIN) || (x > x_MAX) || (y < y_MIN) || (y > y_MAX)) {
    *X = 0;
    *Y = 0;
    return;
  }
  *X = (int) ((x - x_MIN) * WIDTH_GLOBAL / (x_MAX - x_MIN));
  *Y = HEIGHT_GLOBAL - (int) ((y - y_MIN) * HEIGHT_GLOBAL / (y_MAX - y_MIN));
}


/**
 * Gibt zu einem Paar BMP X- und Y-Koordinaten
 * die mathematischen x- und y-Koordinaten aus.
 *
 * X - Wert zwischen 0 und WIDTH_GLOBAL.
 * Y - Wert zwischen 0 und HEIGHT_GLOBAL.
 * x - Berechnete mathematische Koordinate zwischen x_MIN und x_MAX.
 * y - Berechnete mathematische Koordinate zwischen y_MIN und y_MAX.
 */
void toMath(int X, int Y, double* x, double* y,int x_MIN,int x_MAX, int y_MIN, int y_MAX) {
  if ((X < 0) || (X > WIDTH_GLOBAL) || (Y < 0) || (Y > HEIGHT_GLOBAL)) {
    *x = x_MIN;
    *y = y_MIN;
    return;
  }
  *x = x_MIN + ((double) X * (x_MAX - x_MIN)) / WIDTH_GLOBAL;
  *y = y_MIN + ((double) (HEIGHT_GLOBAL - Y) * (y_MAX - y_MIN)) / HEIGHT_GLOBAL;
}

void effect_wandernder_balken(SDL_Renderer* renderer, int input_signal) {
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, input_signal + i, 0, input_signal + i, HEIGHT_GLOBAL);
	}
}
void effect_dummy(SDL_Renderer* renderer, int input_signal) {

}

//Hier hat Caspar was gemacht (etwas ausprobieren)
void effect_linieausprobieren(SDL_Renderer* renderer, int input_signal){
    SDL_RenderDrawLine(renderer, 100, 100, 200,200);
}

void effect_array(SDL_Renderer* renderer, char* pixel_array ) {
    for(int y=0;y<HEIGHT_GLOBAL;y++){
        for(int x=0;x<WIDTH_GLOBAL;x++){
        if (pixel_array[y*WIDTH_GLOBAL+x]==1){
        SDL_RenderDrawPoint(renderer,x,y);
        }
        }
        }

}
void effect_rand_points(SDL_Renderer* renderer, int input_signal,int num_points) {// random Punkte
    int i;
    int width;
    int height;
    srand(input_signal);
    for( i = 0 ; i < num_points ; i++ ) {
        width=rand() % WIDTH_GLOBAL;
        height=rand() % HEIGHT_GLOBAL;
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

void effect_func_quad(SDL_Renderer* renderer, float radius, int o_x, int o_y){// quadratische Funktion
    /* Issues: Strich am oberen rand
       Issues: Keine durchgehende Linie
    */
    char *screen;
    int X,Y;
    screen=calloc(HEIGHT_GLOBAL*WIDTH_GLOBAL,sizeof(char));
    int XX, YY;
    for (int X = 0; X < WIDTH_GLOBAL; X++) {
    double x,y;
    double of_y;
    toMath(X-o_x+WIDTH_GLOBAL/2, HEIGHT_GLOBAL/2+o_y, &x, &of_y,-16,16,-9,9);          // Nur x interessiert
    toBMP(x,x*x*radius+of_y, &XX, &YY,-16,16,-9,9);
    screen[YY*WIDTH_GLOBAL+X]=1;
    screen[(YY+1)*WIDTH_GLOBAL+X]=1;
    screen[(YY+2)*WIDTH_GLOBAL+X]=1;
    screen[(YY+3)*WIDTH_GLOBAL+X]=1;
    screen[(YY+4)*WIDTH_GLOBAL+X]=1;
    }
    effect_array(renderer,screen);
    free(screen);
}
void effect_func_sin(SDL_Renderer* renderer, float amplitude,float streckung, int o_x, int o_y){// Sinusfunktion printen
    /* Issues: Strich am oberen rand
       Issues: Keine durchgehende Linie


    */
    char *screen;
    int X,Y;
    screen=calloc(HEIGHT_GLOBAL*WIDTH_GLOBAL,sizeof(char));
    int XX, YY;
    for (int X = 0; X < WIDTH_GLOBAL; X++) {
    double x,y;
    double of_y;
    toMath(X-o_x+WIDTH_GLOBAL/2, HEIGHT_GLOBAL/2+o_y, &x, &of_y,-16,16,-9,9);          // Nur x interessiert
    toBMP(x,-amplitude*sin(x*streckung), &XX, &YY,-16,16,-9,9);
    screen[YY*WIDTH_GLOBAL+X]=1;
    screen[(YY+1)*WIDTH_GLOBAL+X]=1;
    screen[(YY+2)*WIDTH_GLOBAL+X]=1;
    screen[(YY+3)*WIDTH_GLOBAL+X]=1;
    screen[(YY+4)*WIDTH_GLOBAL+X]=1;
    }
    effect_array(renderer,screen);
    free(screen);
}
void effect_coord(SDL_Renderer* renderer){//Koordinatensystem printen
    char *screen;
    int X,Y;
    screen=calloc(HEIGHT_GLOBAL*WIDTH_GLOBAL,sizeof(char));
    int XX, YY;

    toBMP(0.0, 0.0, &XX, &YY,-16,16,-9,9);
    for (int X = 0; X < WIDTH_GLOBAL; X++) {
        screen[YY * WIDTH_GLOBAL + X] = 1;
        }
    for (int Y = 0; Y < HEIGHT_GLOBAL; Y++) {
        screen[Y * WIDTH_GLOBAL + XX] = 1;
        }
    effect_array(renderer,screen);
    free(screen);

}

#endif // EFFECT_H_INCLUDED
