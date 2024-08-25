#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "io/File.hpp"

#include <unistd.h>
#include <bits/algorithmfwd.h>

#include "opengl/VAO.hpp"
#include "opengl/BufferObject.hpp"
#include "opengl/ShaderProgram.hpp"
#include "opengl/Texture.hpp"
#include "stb/Image.hpp"

void handleWindowEvent(const SDL_Event& event, SDL_Window* window, int& windowWidth, int& windowHeight);
void handleKeyboardKeydownEvent(const SDL_Event& event, bool& quit, float& mixTexture);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    stb::Image::flipVerticallyOnLoad(true);

    int windowWidth = 512;
    int windowHeight = 512;

    SDL_Window* window = SDL_CreateWindow(
        "OpenGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN |
        SDL_WINDOW_UTILITY
    );

    if (window == nullptr)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (context == nullptr)
    {
        std::cerr << "Error creating context: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_MakeCurrent(window, context);

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    const auto shader = std::make_unique<opengl::ShaderProgram>(
        std::make_unique<io::File>("resources/shaders/image-texture/image-texture.vert")->getContent(),
        std::make_unique<io::File>("resources/shaders/image-texture/image-texture.frag")->getContent()
    );
    const GLint vertexPositionAttrib = shader->getAttributeLocation("vertexPosition");
    const GLint vertexColorAttrib = shader->getAttributeLocation("vertexColor");
    const GLint vertexTexCoordAttrib = shader->getAttributeLocation("vertexTexCoord");

    // @formatter:off
    constexpr std::array vertices = {
        // positions       // colors         // texture coords
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f,          // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f,          // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f,          // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.45f, 0.55f           // top left
    };
    // @formatter:on
    constexpr std::array<unsigned int, 6> verticesIndex = {
        0, 1, 2, // first triangle vertices index (top right, bottom right, bottom left)
        0, 2, 3 // second triangle vertices index (top right, bottom left, top left)
    };

    // Generate OpenGL Texture

    const auto texture1 = std::make_unique<opengl::Texture>(
        GL_TEXTURE_2D, "resources/textures/awesomeface.png",GL_RGBA, GL_REPEAT, GL_LINEAR
    );
    const auto texture2 = std::make_unique<opengl::Texture>(
        GL_TEXTURE_2D, "resources/textures/wooden_container.jpg", GL_RGB, GL_CLAMP_TO_EDGE, GL_NEAREST
    );

    // ...

    const auto vao = std::make_unique<opengl::VAO>();
    const auto vbo = std::make_unique<opengl::BufferObject>(GL_ARRAY_BUFFER);
    const auto ebo = std::make_unique<opengl::BufferObject>(GL_ELEMENT_ARRAY_BUFFER);

    vao->use();

    ebo->sendData(verticesIndex.data(), verticesIndex.size() * sizeof(int), GL_STATIC_DRAW);
    vbo->sendData(vertices.data(), vertices.size() * sizeof(float),GL_STATIC_DRAW);

    constexpr GLint vertexPositionSize = 3;
    constexpr GLint vertexColorSize = 3;
    constexpr GLint vertexTexCoordSize = 2;

    constexpr GLsizei stride = (vertexPositionSize + vertexColorSize + vertexTexCoordSize) * sizeof(float);
    const auto vertexColorOffset = (void*)(vertexPositionSize * sizeof(float));
    const auto vertexTexCoordOffset = (void*)((vertexPositionSize + vertexColorSize) * sizeof(float));

    glVertexAttribPointer(vertexPositionAttrib, vertexPositionSize,GL_FLOAT,GL_FALSE, stride, nullptr);
    glVertexAttribPointer(vertexColorAttrib, vertexColorSize,GL_FLOAT,GL_FALSE, stride, vertexColorOffset);
    glVertexAttribPointer(vertexTexCoordAttrib, vertexTexCoordSize,GL_FLOAT,GL_FALSE, stride, vertexTexCoordOffset);

    glEnableVertexAttribArray(vertexPositionAttrib);
    glEnableVertexAttribArray(vertexColorAttrib);
    glEnableVertexAttribArray(vertexTexCoordAttrib);

    float mixTexture = 0.5f;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                handleKeyboardKeydownEvent(event, quit, mixTexture);
                break;
            case SDL_WINDOWEVENT:
                handleWindowEvent(event, window, windowWidth, windowHeight);
                break;
            default: break;
            }
        }

        glViewport(0.0f, 0.0f, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();

        shader->setUniform1i("texture1", 0);
        shader->setUniform1i("texture2", 1);
        shader->setUniform1f("mixTexture", mixTexture);

        vao->use();
        texture1->setActive(GL_TEXTURE0);
        texture2->setActive(GL_TEXTURE1);

        glDrawElements(GL_TRIANGLES, verticesIndex.size(), GL_UNSIGNED_INT, nullptr);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handleWindowEvent(const SDL_Event& event, SDL_Window* window,
                       int& windowWidth, int& windowHeight)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
    {
        std::cout << "Window resized to " << event.window.data1 << "x" << event.window.data2 << std::endl;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    }
}

void handleKeyboardKeydownEvent(const SDL_Event& event, bool& quit, float& mixTexture)
{
    switch (event.key.keysym.sym)
    {
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
    case SDLK_UP:
        mixTexture += 0.1f;

        if (mixTexture > 1.0f)
        {
            mixTexture = 1.0f;
        }

        break;
    case SDLK_DOWN:
        mixTexture -= 0.1f;

        if (mixTexture < 0.0f)
        {
            mixTexture = 0.0f;
        }

        break;
    default: break;
    }
}
