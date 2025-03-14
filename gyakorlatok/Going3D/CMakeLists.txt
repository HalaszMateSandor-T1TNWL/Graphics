cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Going3D)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Going3D src/main.c src/Window/render.c)
target_include_directories(Going3D PRIVATE include)

#target_link_libraries(Going3D PUBLIC mingw32 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image)

target_link_libraries(Going3D PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image)