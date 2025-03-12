cmake_minimum_required(VERSION 3.14)

project(Matrices)

add_executable(Matrices src/main.c src/Matrix/matrix.c src/Matrix/transformations.c)

target_include_directories(Matrices PRIVATE include)