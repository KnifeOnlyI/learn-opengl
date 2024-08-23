#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Window *window = SDL_CreateWindow(
        "OpenGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_UTILITY
    );

    if (window == nullptr) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (context == nullptr) {
        std::cerr << "Error creating context: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_MakeCurrent(window, context);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                        break;
                        case SDLK_a:
                            glClearColor(0.0f, 0.0f, 0.0f, 0.f);
                        break;
                        case SDLK_r:
                            glClearColor(1.0f, 0.0f, 0.0f, 0.f);
                            break;
                        case SDLK_g:
                            glClearColor(0.0f, 1.0f, 0.0f, 0.f);
                            break;
                        case SDLK_b:
                            glClearColor(0.0f, 0.0f, 1.0f, 0.f);
                            break;
                        default: break;
                    }

                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            std::cout << "Window resized to " << event.window.data1 << "x" << event.window.data2 << std::endl;
                            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                            break;
                        default: break;
                    }

                    break;
                default: break;
            }
        }

        glViewport(0.0f, 0.0f, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
