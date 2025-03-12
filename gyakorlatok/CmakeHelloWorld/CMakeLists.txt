cmake_minimum_required(VERSION 3.14.0)

project(CmakeHelloWorld)
add_executable(CmakeHelloWorld src/main.c src/print/print.c)

target_include_directories(CmakeHelloWorld PRIVATE include)