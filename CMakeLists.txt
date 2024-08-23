cmake_minimum_required(VERSION 3.29)

set(PROJECT_NAME learnopengl)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

file(
    GLOB_RECURSE
    SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/core/src/*.c
    ${CMAKE_CURRENT_LIST_DIR}/core/src/*.cpp
)

file(
    GLOB_RECURSE
    THIRD_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.c
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.cpp
)

file(
    GLOB_RECURSE
    HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.h
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/core/header/*.inl
)

file(
    GLOB_RECURSE
    THIRD_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.h
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/third/**/*.inl
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/core/header)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third/glad/include)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${THIRD_SOURCES} ${HEADERS} ${THIRD_HEADERS}
    core/header/opengl/ShaderProgram.hpp
    core/header/opengl/Shader.hpp
    core/header/opengl/OpenGLResource.hpp
    core/src/opengl/Shader.cpp
    core/src/opengl/ShaderProgram.cpp
    core/header/io/File.hpp
    core/src/io/File.cpp
    core/header/opengl/VAO.hpp
    core/src/opengl/VAO.cpp
    core/header/opengl/VBO.hpp
    core/src/opengl/VBO.cpp
)
target_link_libraries(learnopengl SDL2::SDL2)
# If problems happens...
# target_link_libraries(learnopengl SDL2::SDL2 GL X11 pthread Xrandr Xi dl)


