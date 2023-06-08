#include "include/SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
int last_frame_time = 0;

struct ball{
    int x;
    int y;
    int width;
    int height;
}ball;

int process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        return 0;
        break;
    case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return 0;
            }
        break;
    default:
        break;
    }
    return 1;
}

void update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), last_frame_time + FRAME_TARGET_TIME));

    last_frame_time = SDL_GetTicks();

    ball.x += 2;
    ball.y += 1;
}

void setup()
{
    ball.x = 20;
    ball.y = 20;
    ball.width = 15;
    ball.height =15;
}

void renderf(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    SDL_Rect ball_obj = {
        (int)ball.x,
        (int)ball.y,
        (int)ball.width,
        (int)ball.height};
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &ball_obj);

    SDL_RenderPresent(render);

}

void destroy_windows(SDL_Renderer *render, SDL_Window *window)
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    SDL_Window *window = NULL;
    SDL_Renderer * render = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error in INIT");
        return 0;
    }else{
        window = SDL_CreateWindow("Test1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_RESIZABLE);

        if (window == NULL)
        {
            printf("Error in WINDOW");
            return 0;
        }

        render = SDL_CreateRenderer(window, -1, 0);

        if (render == NULL)
        {
            printf("Error in render");
            return 0;
        }
    }

    int loop = 1;
    setup();

    while(loop)
    {
        loop = process_input();
        update();
        renderf(render);

    }

    destroy_windows(render, window);

    return 1;
}
