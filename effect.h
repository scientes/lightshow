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
}function_start_time;

struct function_start_time speicher[100];

void toBMP_alt(double x, double y, int* X, int* Y,int x_MIN,int x_MAX, int y_MIN, int y_MAX) { //in Benutzung
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
  *x = x_MIN + ((double) X * (x_MAX - x_MIN)) / WIDTH_GLOBAL;
  *y = y_MIN + ((double) (HEIGHT_GLOBAL - Y) * (y_MAX - y_MIN)) / HEIGHT_GLOBAL;
}


struct SDL_Point vektorwinder(int x_alt,int y_alt, float angle,int x, int y ){
    struct SDL_Point new_point;
    new_point.x=x+cos(angle)*(x_alt-x)-sin(angle)*(y_alt-y);
    new_point.y=y+sin(angle)*(x_alt-x)+cos(angle)*(y_alt-y);
    return new_point;
}
double length_points(int x1,int y1, int x2, int y2){
 return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}



void effect_wandernder_balkenY(SDL_Renderer* renderer, position,float angle) {
	struct SDL_Point x_neu;
	struct SDL_Point y_neu;
	for (int i = 0;i < 10;i++) {
	    x_neu = vektorwinder(position +i, 0, angle, WIDTH_GLOBAL/ 2, HEIGHT_GLOBAL/2);
	    y_neu = vektorwinder(position +i, HEIGHT_GLOBAL, angle,WIDTH_GLOBAL/2, HEIGHT_GLOBAL/2);
		SDL_RenderDrawLine(renderer, x_neu.x, x_neu.y, y_neu.x, y_neu.y);
	}
}

void effect_wandernder_balkenX(SDL_Renderer* renderer, position) {
	for (int i = 0;i < 10;i++) {
		SDL_RenderDrawLine(renderer, 0, position + i, WIDTH_GLOBAL, position + i);
	}
}
void effect_balken_kreis(SDL_Renderer* renderer, position,float angle){
    struct SDL_Point x_neu;
	struct SDL_Point y_neu;
	angle *= -1;
	for (int i = 0;i < 10;i++) {
	    x_neu = vektorwinder(position +i, 0, angle, WIDTH_GLOBAL/ 2, HEIGHT_GLOBAL/2);
	    y_neu = vektorwinder(position +i, HEIGHT_GLOBAL, angle,WIDTH_GLOBAL/2, HEIGHT_GLOBAL/2);
		SDL_RenderDrawLine(renderer, x_neu.x, x_neu.y, y_neu.x, y_neu.y);
	}
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

void effect_rand_points(SDL_Renderer* renderer, int input_signal,int num_points) {// random Punkte (ziemlich cool)
    int i;
    int width;
    int height;
    srand(input_signal);
    for( i = 0 ; i < num_points ; i++ ) {
        width=rand() % WIDTH_GLOBAL;
        height=rand() % HEIGHT_GLOBAL;
        for(int y = -10; y < 10; y++){
            for(int x = -10; x < 10; x++){
                SDL_RenderDrawPoint(renderer,width + x,height +y);
            }
        }
        }
    }

void effect_func_quad_alt(SDL_Renderer* renderer, float radius, float angle, int o_x, int o_y){// quadratische Funktion
    /* Issues: Strich am oberen rand
       Issues: Keine durchgehende Linie
    */
    SDL_Point* screen=calloc(WIDTH_GLOBAL,sizeof(SDL_Point));
    double x,y;
    int YY,XX;

    for(int i=0;i<WIDTH_GLOBAL;i++){
        toMath(i,0,&x,&y,-16,16,-9,9);
        toBMP_alt(x,sin(x)*radius,&XX,&YY,-16,16,-9,9);
        struct SDL_Point new_point=vektorwinder(XX,YY,angle,o_x,o_y);
        XX=new_point.x;
        YY=new_point.y;
        screen[i].x=XX;
        screen[i].y=YY;
    }
    for(int j=1;j<WIDTH_GLOBAL;j++){
        SDL_RenderDrawLine(renderer,screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
        //printf("From(%d,%d) to(%d,%d)\n",screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
    }

    free(screen);
}

void effect_func_kreis_unten(SDL_Renderer* renderer, float radius, int o_x, int o_y){// quadratische Funktion
    /* Issues: Strich am oberen rand
       Issues: Keine durchgehende Linie
    */
    SDL_Point* screen=calloc(WIDTH_GLOBAL,sizeof(SDL_Point));
    double x,y;
    int YY,XX;
    for(int i=0;i<WIDTH_GLOBAL;i++){
        toMath(i,0,&x,&y,-16,16,-9,9);
        float ergebnis=-sqrt((-(x*x)+radius*radius));
        if (ergebnis==ergebnis){
        toBMP_alt(x,ergebnis,&XX,&YY,-16,16,-9,9);
        screen[i].x=XX;
        screen[i].y=YY;}
        else{
        screen[i].x=0;
        screen[i].y=0;
        }
    }

    for(int j=1;j<WIDTH_GLOBAL;j++){
        if((screen[j].x!=0)&&(screen[j].y!=0)&&(screen[j-1].x!=0)&&(screen[j-1].y!=0)){
        SDL_RenderDrawLine(renderer,screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
        //printf("From(%d,%d) to(%d,%d)\n",screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
        }
    }

    free(screen);
}
void effect_func_kreis_oben(SDL_Renderer* renderer, float radius, int o_x, int o_y){// quadratische Funktion
    /* Issues: Strich am oberen rand
       Issues: Keine durchgehende Linie
    */
    SDL_Point* screen=calloc(WIDTH_GLOBAL,sizeof(SDL_Point));
    double x,y;
    int YY,XX;
    for(int i=0;i<WIDTH_GLOBAL;i++){
        toMath(i,0,&x,&y,-16,16,-9,9);
        float ergebnis=sqrt((-(x*x)+radius*radius));
        if (ergebnis==ergebnis){
        toBMP_alt(x,ergebnis,&XX,&YY,-16,16,-9,9);
        screen[i].x=XX;
        screen[i].y=YY;}
        else{
        screen[i].x=0;
        screen[i].y=0;
        }
    }

    for(int j=1;j<WIDTH_GLOBAL;j++){
        if((screen[j].x!=0)&&(screen[j].y!=0)&&(screen[j-1].x!=0)&&(screen[j-1].y!=0)){
        SDL_RenderDrawLine(renderer,screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
        //printf("From(%d,%d) to(%d,%d)\n",screen[j-1].x,screen[j-1].y,screen[j].x,screen[j].y);
        }
    }

    free(screen);
}

void effect_coord(SDL_Renderer* renderer){//Koordinatensystem printen
    char *screen;
    int X,Y;
    screen=calloc(HEIGHT_GLOBAL*WIDTH_GLOBAL,sizeof(char));
    int XX, YY;

    toBMP_alt(0.0, 0.0, &XX, &YY,-16,16,-9,9);
    for (int X = 0; X < WIDTH_GLOBAL; X++) {
        screen[YY * WIDTH_GLOBAL + X] = 1;
        }
    for (int Y = 0; Y < HEIGHT_GLOBAL; Y++) {
        screen[Y * WIDTH_GLOBAL + XX] = 1;
        }
    effect_array(renderer,screen);
    free(screen);
}

void effect_3D_sinus(SDL_Renderer* renderer,int radius){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
            for(int i = -10; i < 10; i++){
            effect_func_quad_alt(renderer,radius*0.02,1.57082144*2,WIDTH_GLOBAL/2+i,HEIGHT_GLOBAL/2+i);
}
}

#endif // EFFECT_H_INCLUDED
