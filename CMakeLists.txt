cmake_minimum_required(VERSION 3.29)
project(learnopengl)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(learnopengl main.cpp)

target_link_libraries(learnopengl SDL2::SDL2)


