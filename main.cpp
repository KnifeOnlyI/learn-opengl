#include <iostream>
#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

    SDL_Delay(1000);

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
