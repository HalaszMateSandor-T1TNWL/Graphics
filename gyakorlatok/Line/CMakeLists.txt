cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Line)

find_package(OpenGL REQUIRED)

add_executable(Line src/main.c)
target_include_directories(Line PRIVATE include)

target_link_libraries(Line PUBLIC mingw32 SDL2main SDL2 OpenGL::GL)