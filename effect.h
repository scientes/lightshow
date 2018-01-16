#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

//Funktion toMath: Überesetzung der mathematischen in die BitMaap Koordinaten
void toMath(int X, int Y, int *x, int *y,int BREITE,int HOEHE){              //x,y mathematisch; X,Y Bitmap Koordinaten
    int xmin = - (BREITE / 2);
    int xmax = BREITE / 2;
    int ymin = - (HOEHE / 2);
    int ymax = HOEHE / 2;
    *x = xmin + ((X * (xmax - xmin)) / BREITE);     //Umsetzung der Formeln asu der Aufgabenstellung    für die X-Achse
    *y = -1 * (ymin + ((Y * (ymax - ymin)) / HOEHE));//Umsetzung der Formeln asu der Aufgabenstellung   für die Y-Achse
}
//Funktion toBMP: Verarbeitung der Parameter und Übergabe an den screen
void toscreen (int x, int y, int *X, int *Y, int BREITE, int HOEHE){
    int xmin = - (BREITE / 2);
    int xmax = BREITE / 2;
    int ymin = - (HOEHE / 2);
    int ymax = HOEHE / 2;
    *X = ((x - xmin) * BREITE)/(xmax - xmin);
    *Y = ((-y -ymin) * HOEHE) / (ymax - ymin);
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
        if (pixel_array[y*width_glo+x]==0){
        SDL_RenderDrawPoint(renderer,x,y);
        }
        }
        }
    free(pixel_array);

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
/*
void effect_circle(SDL_Renderer* renderer,int radius, int x, int y){
    char *screen;
    int X,Y;
    screen=malloc(height_glo*width_glo*sizeof(char));
    for(int y=0;y<height_glo;y++){
        printf("%d\n",y);
        for(int x=0;x<width_glo;x++){
        //printf("%d,%d\n",x,y);
        toscreen(0.0,y,&X,&Y,width_glo,height_glo);
        screen[y*width_glo+X]=1;
        toscreen(x,0.0,&X,&Y,width_glo,height_glo);
        screen[Y*width_glo+x]=1;
        }
        }
    effect_array(renderer,screen);
    free(screen);




}
*/
#endif // EFFECT_H_INCLUDED
