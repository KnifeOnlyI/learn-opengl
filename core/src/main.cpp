#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "io/File.hpp"
#include "opengl/Shader.hpp"
#include "opengl/ShaderProgram.hpp"

#include <unistd.h>

#include "opengl/VAO.hpp"
#include "opengl/BufferObject.hpp"

void handleWindowEvent(const SDL_Event &event, SDL_Window *window, int &windowWidth, int &windowHeight) {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        std::cout << "Window resized to " << event.window.data1 << "x" << event.window.data2 << std::endl;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    }
}

void handleKeyboardKeydownEvent(const SDL_Event &event, bool &quit) {
    switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            quit = true;
            break;
        case SDLK_a:
            glClearColor(0.0f, 0.0f, 0.0f, 0.f);
            break;
        case SDLK_SPACE:
            int polygonMode;
            glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
            glPolygonMode(GL_FRONT_AND_BACK, polygonMode == GL_FILL ? GL_LINE : GL_FILL);
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
}

std::unique_ptr<opengl::ShaderProgram> getSolidColorShaderProgram() {
    const auto vertexShader = std::make_unique<opengl::Shader>(
        std::make_unique<io::File>("resources/shaders/solid-color/solid-color.vert")->getContent(),
        GL_VERTEX_SHADER
    );

    const auto fragmentShader = std::make_unique<opengl::Shader>(
        std::make_unique<io::File>("resources/shaders/solid-color/solid-color.frag")->getContent(),
        GL_FRAGMENT_SHADER
    );

    std::vector shaders {vertexShader.get(), fragmentShader.get()};

    return std::make_unique<opengl::ShaderProgram>(shaders);
}

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

    constexpr std::array rectangleVertices = {
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };
    constexpr std::array<unsigned int, 6> rectangleVerticesIndex = {
        0, 1, 3, // first triangle vertices index (top right, bottom right, top left)
        1, 2, 3 // second triangle vertices index (bottom right, bottom left, top left)
    };

    const auto vao = std::make_unique<opengl::VAO>();
    const auto vbo = std::make_unique<opengl::BufferObject>(GL_ARRAY_BUFFER);
    const auto ebo = std::make_unique<opengl::BufferObject>(GL_ELEMENT_ARRAY_BUFFER);

    opengl::VAO::bind(*vao);

    vbo->use();
    vbo->sendData(rectangleVertices.data(), rectangleVertices.size() * sizeof(float), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    ebo->use();
    ebo->sendData(rectangleVerticesIndex.data(), rectangleVerticesIndex.size() * sizeof(int), GL_STATIC_DRAW);

    const auto solidColorShaderProgram = getSolidColorShaderProgram();

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    handleKeyboardKeydownEvent(event, quit);
                    break;
                case SDL_WINDOWEVENT:
                    handleWindowEvent(event, window, windowWidth, windowHeight);
                    break;
                default: break;
            }
        }

        glViewport(0.0f, 0.0f, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        opengl::VAO::bind(*vao);
        opengl::ShaderProgram::use(*solidColorShaderProgram);

        glDrawElements(GL_TRIANGLES, rectangleVerticesIndex.size(), GL_UNSIGNED_INT, nullptr);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
