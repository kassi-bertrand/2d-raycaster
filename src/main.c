#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "constants.h"
#include "entities.h"

Point light_source;
Point mouse_position;

Segment edges[2] = {
    {75, 100, 200, 400},
    {600, 150, 350, 550}
};

unsigned int game_is_running = FALSE;
SDL_Window *myWindow = NULL;
SDL_Renderer *renderer = NULL;
int last_frame_time = 0;


Point cast_Ray(Segment light_Ray, Segment edge){
/*
    The following algorithm is detailed at:
    https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
*/
    Point Intersept;

    float p0_x = light_Ray.x1;
    float p0_y = light_Ray.y1;

    float p1_x = light_Ray.x2;
    float p1_y = light_Ray.y2;

    float p2_x = edge.x1;
    float p2_y = edge.y1;

    float p3_x = edge.x2;
    float p3_y = edge.y2;

    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;          s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;          s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1){
        Intersept.x = p0_x + (t * s1_x);
        Intersept.y = p0_y + (t * s1_y);

        return Intersept;
    }
    else {
        Intersept.x = NAN;
        Intersept.y = NAN;
        
        return Intersept;
    }

}

float distance(float x1, float y1, float x2, float y2)
{
    float square_difference_x = (x2 - x1) * (x2 - x1);
    float square_difference_y = (y2 - y1) * (y2 - y1);
    float sum = square_difference_x + square_difference_y;
    float value = sqrt(sum);
    return value;
}

void render_Rays (){

    for (float degree = 0; degree < 360; degree++){

        Point closest_Point = {NAN, NAN};
        float record = INFINITY;

        //convert from "deg" to "rad"
        float radian = ( degree * M_PI) / 180.0;

        //Light segment representing a ray from light source
        Segment light_ray = {
            light_source.x,
            light_source.y,
            (light_source.x) + RAY_LENGTH * cos(radian),
            (light_source.y) + RAY_LENGTH * sin(radian)
        };

        for (int i = 0; i < 2; i++){
            Point pt = cast_Ray(light_ray, edges[i]);

            if (pt.x != NAN && pt.y != NAN){
                float d = distance (light_source.x, light_source.y, pt.x, pt.y); // compute distance from light source to pt
                if (d < record){
                    record = d;
                    //closest_Point = pt;
                    light_ray.x2 = pt.x;
                    light_ray.y2 = pt.y;
                }
            }   
        }
        SDL_RenderDrawLine(renderer, light_ray.x1, light_ray.y1, light_ray.x2, light_ray.y2);
        /*
        // if closest point exist
        if (closest_Point.x != NAN && closest_Point.y != NAN){
            SDL_RenderDrawLine(renderer, light_ray.x1, light_ray.y1, closest_Point.x, closest_Point.y);
        }
        else {
            // render a ray that is RAY_LENGTH LONG
            //SDL_RenderDrawLine(renderer, light_ray.x1, light_ray.y1, light_ray.x2, light_ray.y2);
        }*/

    }

}


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
        //mouse movement :)
        case SDL_MOUSEMOTION:
            mouse_position.x = event.motion.x;
            mouse_position.y = event.motion.y;
            break;
        default:
            break;
    }
}

void setup(){
    //TODO: Give game objects their initial position
    light_source.x = 400;
    light_source.y = 400;

}

void update(){
    //TODO: Wait for enough time, then update game objects' positions
    int waiting_time = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if(waiting_time > 0 && waiting_time <= FRAME_TARGET_TIME){
        SDL_Delay(waiting_time);
    }
    last_frame_time = SDL_GetTicks(); //returns time since SDL Initialization
    
    //Update game object position
    light_source.x = mouse_position.x;
    light_source.y = mouse_position.y;
}

void render(){
    //TODO: Render game element onto the screen

    //Set black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    //set drawing color to solid white for "edges" and "light source"
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

        //Render edges
    for (int i = 0; i < 2; i++){
        SDL_RenderDrawLine(renderer, edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2);
    }

        //Render light source
    SDL_RenderDrawPoint(renderer, light_source.x, light_source.y);
    
    //Set drawing color to light white for light rays
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 35);

        //Render each emitted ray from the source
    render_Rays();
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