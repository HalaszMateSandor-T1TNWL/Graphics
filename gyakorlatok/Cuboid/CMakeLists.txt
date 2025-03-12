cmake_minimum_required(VERSION 3.14)

project(Cuboid)

add_executable(Cuboid src/main.c src/Brick/brick.c)
target_include_directories(Cuboid PUBLIC include)