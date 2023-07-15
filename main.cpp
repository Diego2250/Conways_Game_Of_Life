#include <iostream>
#include <fstream>
#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("hola", 0, 0, 1200, 800, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 100, 60, 60, 1);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(10000);

    return 0;
}