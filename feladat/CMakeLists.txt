cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(The_Pillars)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(The_Pillars src/main.c src/application.c src/camera.c src/scene.c src/utils.c src/entity.c src/load_texture.c src/terrain.c src/bounding_box.c )
target_include_directories(The_Pillars PUBLIC include)

if(WIN32)
    target_link_libraries(The_Pillars PUBLIC mingw32 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf obj)
endif(WIN32)

if(UNIX)
    target_link_libraries(The_Pillars PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image obj m)
endif(UNIX)
