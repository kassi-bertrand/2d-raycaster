#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

SDL_Window *myWindow = NULL;
SDL_Renderer *renderer = NULL;

unsigned int initialize_SDL_winodw(void){

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        //something bad happened :(
        fprintf(stderr, "Unable to Initialize SDL\n");
        return FALSE;
    }

    //create window
    myWindow = SDL_CreateWindow(
        NULL, //window title
        SDL_WINDOWPOS_CENTERED, //x-pos
        SDL_WINDOWPOS_CENTERED, //y-pos
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!myWindow){
        fprintf(stderr, "Unable to create a window\n");
        return FALSE;
    }

    //create renderer
    renderer = SDL_CreateRenderer( myWindow, -1, 0);
    if(!renderer != 0){
        fprintf(stderr, "unable to create a renderer\n");
        return FALSE;
    }

    //Everything went okay :)
    return TRUE;
}
int main(int argc, char *argv[]){
    initialize_SDL_winodw();
    return 0;
}