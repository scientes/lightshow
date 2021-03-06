#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "effect.h"
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int rot=0;
int gruen=255;
int blau=0;

unsigned long long milissinceepoch(){       //Funktion um die Milisekunden seit Epoch Ausszugeben. Format ist unsigned long long, um lanjährige Kompatibilität zu gewehrleisten

    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 +(unsigned long long)(tv.tv_usec) / 1000;
    return millisecondsSinceEpoch;

}
int firstfreeelement(struct function_start_time* arr){
    int Last_element=0;
    for(int i=0;i<500;i++){
            if( arr[i].functionid==0){
                Last_element=i;
                break;
            }
            }
    return Last_element;
}

int firstsameelement(struct function_start_time* arr,char func){
    int same_element=0;
    for(int i=0;i<500;i++){
            if( arr[i].functionid==func){
                same_element=i;
                break;
            }
            }
    return same_element;
    }
int main(int argc, char* args[])
{   // initialisiere alle SDL wichtigen Variablen
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    struct function_start_time *fstart;
    fstart=calloc(500,sizeof(function_start_time));

    // struckt zur koordinierung der Funktionen
    struct function_start_time *starttimestruct;
    // initialisier SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init failed!\n");
        }
    else{
    // Wenn erfolgreich initialisiert bestimme Auflösung und Bildwiederholfrequenz des Monitors
    printf("SDL_Init was successful!\n");

    SDL_DisplayMode current;

    for(int i=0;i<SDL_GetNumVideoDisplays();i++){
    int should_be_zero=SDL_GetCurrentDisplayMode(i,&current);
    if(should_be_zero!=0){
    printf("Could not get display mode for video display #%d: %s", i, SDL_GetError());

    }
    else{
    printf("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
    }
    printf("hi\n");
    /*funktioniert zz nicht bei SDL_GetNumVideoDisplays()>1*/
    WIDTH_GLOBAL=current.w;
    HEIGHT_GLOBAL=current.h;
    FPS_CAP=current.refresh_rate;
    }

    // erschaffe Ein Fullscreen Fenster
    window = SDL_CreateWindow("lightshow",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,

				WIDTH_GLOBAL,
				HEIGHT_GLOBAL,
				SDL_WINDOW_OPENGL
				);

    if (window == NULL) {
        // Falls dies scheitert
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    struct presentation {
        int rotierender_balken;
        int randomPoints;
        int presentation;
        int sinus3d;
        int krake;
        int balken;
        int LEFT;
        int DOWN;
    } active;

    //time_t seconds, starttime_pr;
    //seconds = milissinceepoch();
    //starttime_pr = time(NULL);


    active.rotierender_balken = 0;
    active.randomPoints = 0;

    // erstellen des Renderes für das Window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC );
    // Male den Bildschirm schwarz
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // übertrage dies Auf den Bildschirm
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    // Erstelle Alle nötigen Variablen für die Hauptschleife
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	int x=1;
	int position = 0; //für wanderbalken
	int positionY = 0;
	float angle = 0;
	int speed = 500; //für Strobo effekt
	int frames = 0;
	int Color[3]; //speichert Farben
	int t = 1;
	int time;
	int time_running;
	unsigned long long starttime_presentation;
	unsigned long long rendertime=0;
	unsigned long long start;
	unsigned long long stop;
	unsigned long long last_keypressed;
	int h=1,u=0;
	SDL_SetRenderDrawBlendMode(renderer,1);

	int Last_element=0;
	int same_element;
	pthread_t threadid;
	pthread_create(&threadid,NULL,play,NULL);
    while (x){
        // NEhme die Startzeit des Jetzigen Frames
        start=milissinceepoch();
		x++;
		// Update die Tastatur und Fenster inputevents
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		// Lese diese Events aus
        if (milissinceepoch()-last_keypressed>100){

        if (state[SDL_SCANCODE_F]){
            last_keypressed=milissinceepoch();
            if(state[SDL_SCANCODE_LSHIFT]){
                same_element=firstsameelement(fstart,'f');
                fstart[same_element].functionid=0;
                fstart[same_element].starttime=0;
                Last_element=firstfreeelement(fstart);
            }
            else{
                fstart[Last_element].functionid='f';
                fstart[Last_element].starttime=milissinceepoch();
                Last_element=firstfreeelement(fstart);
            }
        }
        if (state[SDL_SCANCODE_K]){
            last_keypressed=milissinceepoch();
            if(state[SDL_SCANCODE_LSHIFT]){
                same_element=firstsameelement(fstart,'k');
                fstart[same_element].functionid=0;
                fstart[same_element].starttime=0;
                Last_element=firstfreeelement(fstart);
            }
            else{
                fstart[Last_element].functionid='k';
                fstart[Last_element].starttime=milissinceepoch();
                Last_element=firstfreeelement(fstart);
            }
        }
        }
        if (state[SDL_SCANCODE_1] || state[SDL_SCANCODE_2] || state[SDL_SCANCODE_3]){
            if(state[SDL_SCANCODE_1]){
                rot = 255;
                gruen = 0;
                blau = 0;
            }
            if(state[SDL_SCANCODE_2]){
                rot = 0;
                gruen = 255;
                blau = 0;
            }
            if(state[SDL_SCANCODE_3]){
                rot = 0;
                gruen = 0;
                blau = 255;
            }

        }
        //printf("%d\n",firstfreeelement(fstart));
        for(int i=0;i<sizeof(fstart);i++){

        switch(fstart[i].functionid){
        case 'f' :
        SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
        effect_func_quad_alt(renderer,1,((double)(milissinceepoch()-fstart[i].starttime)/960),WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
        break;

        case 'k':
        SDL_SetRenderDrawColor(renderer,100,100,100,200);
            effect_coord(renderer);
        break;
        }
        }
        if (state[SDL_SCANCODE_H] || active.sinus3d == 1){
        if(u==100){
            h=-1;
            }
            if(u==-100){
            h=1;
            }
        effect_3D_sinus(renderer,u);
        u+=h;
        }


        if(state[SDL_SCANCODE_B] || active.balken == 1){     //Wandernder Balken
            if (state[SDL_SCANCODE_RIGHT] && position < WIDTH_GLOBAL) {
                if(position < WIDTH_GLOBAL - 4)
                    position += 4;
                else    position = 0;
            }
            if (state[SDL_SCANCODE_LEFT] || active.LEFT == 1) {         //Abfragen für die Richtung, in die der Balken wa
                if(position > 4)
                    position -= 4;
                else    position = WIDTH_GLOBAL;
                }
            if (state[SDL_SCANCODE_UP]){
                if(positionY > 0)
                    positionY -= 4;
                else    positionY = WIDTH_GLOBAL;
            }
            if (state[SDL_SCANCODE_DOWN] || active.DOWN == 1){
                if(positionY < HEIGHT_GLOBAL)
                    positionY +=4;
                else    positionY = 0;
            }

            SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
            effect_wandernder_balkenY(renderer, position, 0);
            SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
            effect_wandernder_balkenX(renderer, positionY);
            }

        if (state[SDL_SCANCODE_N] || active.rotierender_balken == 1){
            SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
            effect_wandernder_balkenY(renderer, WIDTH_GLOBAL/2, angle);
            angle += 0.005;
        }
        if (state[SDL_SCANCODE_M] || active.rotierender_balken == 1){
            SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
            effect_balken_kreis(renderer, WIDTH_GLOBAL/2, angle);
            if( !state[SDL_SCANCODE_N]){
                angle += 0.005;
            }
        }

		if (state[SDL_SCANCODE_R] || active.randomPoints == 1) { //Zufällige Punkte
			//printf("<R> Pressed.\n");
			// Male zufällig Punkte auf den Bildschirm (aus effect.h)
			SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
			effect_rand_points(renderer,x/20,1000);}
            SDL_SetRenderDrawColor(renderer,rot,gruen,blau,255);
        if (state[SDL_SCANCODE_G] || active.krake == 1){
            //effect_func_test_dummy(renderer,u*0.01,0,0);
            if(u==100){
            h=-1;
            }
            if(u==-100){
            h=1;
            }
            //effect_func_quad_alt(renderer,u*0.02,-1.57082144,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            for(int i = -10; i < 10; i++){
            effect_func_quad_alt(renderer,u*0.02,1.57082144*2,WIDTH_GLOBAL/2+i,HEIGHT_GLOBAL/2+i);
            }
            //effect_func_quad_alt(renderer,u*0.02,0,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            effect_func_quad_alt(renderer,u*0.02,-1.57082144/4,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            effect_func_quad_alt(renderer,u*0.02,1.57082144/4,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
            effect_func_quad_alt(renderer,u*0.02,-1.57082144/4*3,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            effect_func_quad_alt(renderer,u*0.02,1.57082144/4*3,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            SDL_SetRenderDrawColor(renderer,255,0,255,255);
            effect_func_quad_alt(renderer,u*0.02,1.57082144,WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            effect_func_quad_alt(renderer,u*0.02,0,800,450);
            SDL_SetRenderDrawColor(renderer,0,255,255,255);
            effect_func_kreis_oben(renderer,exp(u*0.01),WIDTH_GLOBAL/2,HEIGHT_GLOBAL/2);
            effect_func_kreis_unten(renderer,-exp(u*0.01),160,450);
            //effect_func_kreis_oben(renderer,u*0.01-0.02,800,450);
            //effect_func_kreis_unten(renderer,-u*0.01-0.02,800,450);
            u += h;
            //effect_func_sin(renderer,u*0.01,0.5,800,450);
            //SDL_RenderPresent(renderer);
            }

        //Vorfuehrung

        if (state[SDL_SCANCODE_P] || active.presentation == 1){
            active.presentation = 1;

            if (state[SDL_SCANCODE_P]){
            starttime_presentation = milissinceepoch();
            //printf("%d\n", starttime_presentation);
            }

            time_running = (milissinceepoch() - starttime_presentation);


                //die Abfolge
            if(time_running < 2000){
                active.rotierender_balken = 1;
            }
            if(time_running > 2000 && time_running < 4000){
                active.rotierender_balken = 0;
                active.randomPoints = 1;
            }
            if(time_running > 4000 && time_running < 6000){
                active.randomPoints = 0;
                active.sinus3d = 1;
            }
            if(time_running > 6000 && time_running < 10000){
                active.sinus3d = 0;
                active.krake = 1;
            }
            if(time_running > 10000 && time_running < 15000){
                active.krake = 0;
                active.balken = 1;
                active.LEFT = 1;
                active.DOWN = 1;
            }
            if(time_running > 15000)
                //starttime_presentation = milissinceepoch();
                active.balken = 0;
                active.LEFT = 0;
                active.DOWN = 0;



            if(state[SDL_SCANCODE_0]){
                active.presentation = 0;
            }

        }





        SDL_RenderPresent(renderer); // Zeichne die Berechnungen auf den BIldschirm
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);// Male den Bildschirm Schwarz
		if (x%10==0){ // Abbruchbedingungen
            if(event.type==256){// 256=Exitkreuz
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
		rendertime+=time;// brechene die Zeit die Für den Frame gebraucht wurde
		if (frames%FPS_CAP){
            //printf("Avarage rendertime in ms: %d\n",rendertime/frames);// printe den Durchschnitt
		}
    if (time<(1000/FPS_CAP)){
        SDL_Delay((1000/FPS_CAP)-time);// Minimiere den Delay um die Renderzeit
    }

    }
    }
    free(fstart);
    SDL_DestroyWindow(window);// Räume auf

    SDL_Quit();
  return 0;
}


