#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "effect.h"
#include <time.h>
#include <sys/time.h>

unsigned long long milissinceepoch(){       //Funktion um die Milisekunden seit Epoch Ausszugeben. Format ist unsigned long long, um lanjährige Kompatibilität zu gewehrleisten


    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long long millisecondsSinceEpoch = (unsigned long long)(tv.tv_sec) * 1000 +(unsigned long long)(tv.tv_usec) / 1000;
    return millisecondsSinceEpoch;

}

int main(int argc, char* args[])
{   // initialisiere alle SDL wichtigen Variablen
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
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
				SDL_WINDOW_OPENGL || SDL_WINDOW_FULLSCREEN
				);

    if (window == NULL) {
        // Falls dies scheitert
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
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
	int t=0;
	int speed = 500; //für Strobo effekt
	int frames=0;
	unsigned long long rendertime=0;
	unsigned long long start;
	unsigned long long stop;
	unsigned long long time;
	int u;
	SDL_SetRenderDrawBlendMode(renderer,1);
    while (x){
        // NEhme die Startzeit des Jetzigen Frames
        start=milissinceepoch();
		x++;
		// Update die Tastatur und Fenster inputevents
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		u+=1;
		// Lese diese Events aus
        if(state[SDL_SCANCODE_B]){     //Wandernder Balken
            if (t<0){
                t=WIDTH_GLOBAL;
            }
            if (state[SDL_SCANCODE_RIGHT]) {
                //printf("<RIGHT> is pressed.\n");
                t+=2;
            }
            if (state[SDL_SCANCODE_LEFT]) {
                //printf("<LEFT> is pressed.\n");
                t-=2;
                }
            SDL_SetRenderDrawColor(renderer,0,255,0,255);
            effect_wandernder_balken(renderer, t);

        }
		if (state[SDL_SCANCODE_R]) { //Zufällige Punkte
			//printf("<R> Pressed.\n");
			// Male zufällig Punkte auf den Bildschirm (aus effect.h)
			SDL_SetRenderDrawColor(renderer,200,0,0,255);
			effect_rand_points(renderer,x%10,50);}

		if (state[SDL_SCANCODE_4]){             //Caspar Hello world linie
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            effect_linieausprobieren(renderer, 1);
		}

		if(state[SDL_SCANCODE_F]){ //funktion wird ausgegeben


            SDL_SetRenderDrawColor(renderer,0,0,255,255);

            //effect_func_test_dummy(renderer,u*0.01,0,0);
            effect_func_quad(renderer,log(u*0.01),WIDTH_GLOBAL/2,0);
            //effect_func_sin(renderer,u*0.01,0.5,800,450);
            //SDL_RenderPresent(renderer);

		}
		if(state[SDL_SCANCODE_S]){
            printf("Strobo aktiviert");
            if(state[SDL_SCANCODE_UP])
                speed -= 50;
            if(state[SDL_SCANCODE_DOWN])
                speed += 50;

            effect_Strobo(renderer, speed);


		}



		//SDL_SetRenderDrawColor(renderer,100,100,100,200);
        //    effect_coord(renderer);


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
            printf("Avarage rendertime in ms: %d\n",rendertime/frames);// printe den Durchschnitt
		}
    if (time<(1000/FPS_CAP)){
        SDL_Delay((1000/FPS_CAP)-time);// Minimiere den Delay um die Renderzeit
    }
    }
    SDL_DestroyWindow(window);// Räume auf
    }
    SDL_Quit();
  return 0;
}

