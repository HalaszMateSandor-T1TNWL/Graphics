cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Camera_Movement)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Camera_Movement src/main.c src/camera.c src/scene.c src/utils.c src/app_window.c)
target_include_directories(Camera_Movement PRIVATE include)

if(WIN32)
target_link_libraries(Camera_Movement PUBLIC mingw32 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image)
endif(WIN32)

if(UNIX)
target_link_libraries(Camera_Movement PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image m)
endif(UNIX)