#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#include <SDL2/SDL.h>

#define MUS_PATH "nero.wav"

// prototype for our audio callback
// see the implementation for more information

// variable declarations
static Uint8 *audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play
void my_audio_callback(void *userdata, Uint8 *stream, unsigned int len) {

	if (audio_len ==0)
		return;

	len = ( len > audio_len ? audio_len : len );
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}

/*
** PLAYING A SOUND IS MUCH MORE COMPLICATED THAN IT SHOULD BE
*/
Uint8* play(){
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
			return 1;

	// local variables
	static Uint32 wav_length; // length of our sample
	static Uint8 *wav_buffer; // buffer containing our audio file
	static SDL_AudioSpec wav_spec; // the specs of our piece of music

    printf("hi");
	/* Load the WAV */
	// the specs, length and buffer of our wav are filled
	if( SDL_LoadWAV(MUS_PATH, &wav_spec, &wav_buffer, &wav_length) == NULL ){
	  return 1;
	}
	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;

	// set our global static variables
	audio_pos = wav_buffer; // copy sound buffer
	audio_len = wav_length; // copy file length

	/* Open the audio device */
	printf("%d\n",wav_spec.freq);
	if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
	  fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}
    printf("%d\n",wav_spec.freq);
	/* Start playing */
	SDL_PauseAudio(0);


	// wait until we're don't playing
	while ( audio_len > 0 ) {
		SDL_Delay(10);
	}

	// shut everything down
	atexit(abort_play(wav_buffer));

}
void abort_play(Uint8* wav_buf){
    SDL_CloseAudio();
	SDL_FreeWAV(wav_buf);

}

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



void effect_wandernder_balkenY(SDL_Renderer* renderer, int position,float angle) {
	struct SDL_Point x_neu;
	struct SDL_Point y_neu;
	for (int i = 0;i < 10;i++) {
	    x_neu = vektorwinder(position +i, 0, angle, WIDTH_GLOBAL/ 2, HEIGHT_GLOBAL/2);
	    y_neu = vektorwinder(position +i, HEIGHT_GLOBAL, angle,WIDTH_GLOBAL/2, HEIGHT_GLOBAL/2);
		SDL_RenderDrawLine(renderer, x_neu.x, x_neu.y, y_neu.x, y_neu.y);
	}
}

void effect_wandernder_balkenX(SDL_Renderer* renderer,int position) {
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
