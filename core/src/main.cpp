#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "io/File.hpp"

#include <unistd.h>

#include "opengl/VAO.hpp"
#include "opengl/BufferObject.hpp"
#include "opengl/ShaderProgram.hpp"

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

    const auto solidColorShaderProgram = std::make_unique<opengl::ShaderProgram>(
        std::make_unique<io::File>("resources/shaders/solid-color/solid-color.vert")->getContent(),
        std::make_unique<io::File>("resources/shaders/solid-color/solid-color.frag")->getContent()
    );
    const auto vertexColorShaderProgram = std::make_unique<opengl::ShaderProgram>(
        std::make_unique<io::File>("resources/shaders/vertex-color/vertex-color.vert")->getContent(),
        std::make_unique<io::File>("resources/shaders/vertex-color/vertex-color.frag")->getContent()
    );

    const GLint solidColorShaderPositionAttribLocation = solidColorShaderProgram->getAttributeLocation("position");

    const GLint vertexColorShaderPositionAttribLocation = vertexColorShaderProgram->getAttributeLocation("position");
    const GLint vertexColorShaderColorAttribLocation = vertexColorShaderProgram->getAttributeLocation("color");

    constexpr std::array leftTriangleVertices = {
        -0.5f, 0.25f, 0.0f, // top
        -0.75f, -0.25f, 0.0f, // bottom left
        -0.25f, -0.25f, 0.0f // bottom right
    };

    constexpr std::array rightTriangleVertices = {
        0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 0.0f, // top left (red)
        0.75f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f, // top right (green)
        0.5f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom (blue)
    };

    const auto leftTriangleVAO = std::make_unique<opengl::VAO>();
    const auto leftTriangleVBO = std::make_unique<opengl::BufferObject>(GL_ARRAY_BUFFER);

    const auto rightTriangleVAO = std::make_unique<opengl::VAO>();
    const auto rightTriangleVBO = std::make_unique<opengl::BufferObject>(GL_ARRAY_BUFFER);

    leftTriangleVAO->use();
    leftTriangleVBO->sendData(leftTriangleVertices.data(), leftTriangleVertices.size() * sizeof(float), GL_STATIC_DRAW);

    glVertexAttribPointer(
        solidColorShaderPositionAttribLocation,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        nullptr
    );
    glEnableVertexAttribArray(solidColorShaderPositionAttribLocation);

    rightTriangleVAO->use();
    rightTriangleVBO->sendData(rightTriangleVertices.data(), rightTriangleVertices.size() * sizeof(float), GL_STATIC_DRAW);

    glVertexAttribPointer(
        vertexColorShaderPositionAttribLocation,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 6,
        nullptr
    );
    glEnableVertexAttribArray(vertexColorShaderPositionAttribLocation);

    glVertexAttribPointer(
        vertexColorShaderColorAttribLocation,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 6,
        reinterpret_cast<void *>(3 * sizeof(float))
    );
    glEnableVertexAttribArray(vertexColorShaderColorAttribLocation);

    float color = 1.0f;

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

        solidColorShaderProgram->use();
        solidColorShaderProgram->setUniform4f("color", color, 1.0f, 1.0f - color, 1.0f);

        leftTriangleVAO->use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        vertexColorShaderProgram->use();
        vertexColorShaderProgram->setUniform3f("offset", 0.25f, 0.25f, 0.25f);

        rightTriangleVAO->use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);

        color -= 0.01f;

        if (color < 0.0f) {
            color = 1.0f;
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
