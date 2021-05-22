#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

unsigned int game_is_running = FALSE;
SDL_Window *myWindow = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;

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
void process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
        
        default:
            break;
    }
}

void setup(){
    //TODO:
}

void update(){
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));
    float delta_time = (SDL_GetTicks() - last_frame_time)/1000.0f;
    
    last_frame_time = SDL_GetTicks(); //returns time since SDL Initialization
}

void render(){
    //TODO:
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw game objects here
        //my edges
        //my point (light source)
        //rays from the light source


    //present the back buffer
    SDL_RenderPresent(renderer);
}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(myWindow);
    SDL_Quit();
}


int main(int argc, char *argv[]){
    game_is_running = initialize_SDL_winodw();

    //My setup function
    setup();

    //As long as game is running the game loop runs
    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}