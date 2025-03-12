cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Going3D)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Going3D src/main.c src/Window/cleanup.c)
target_include_directories(Going3D PRIVATE include)

target_link_libraries(Going3D PUBLIC mingw32 SDL2Main SDL2::SDL2 OpenGL::GL glu32)