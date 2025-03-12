cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH "C:/MinGW/include/SDL2")

project(AdvancedSDL)

add_executable(AdvancedSDL src/main.c)

target_include_directories(AdvancedSDL PRIVATE include)
target_link_libraries(AdvancedSDL PUBLIC SDL2  mingw32)
