cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Character_Movement)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(OpenGL REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Character_Movement src/main.c src/application.c src/camera.c src/scene.c src/utils.c src/entity.c src/load_texture.c src/terrain.c src/bounding_box.c)
target_include_directories(Character_Movement PUBLIC include)

if(WIN32)
target_link_libraries(Character_Movement PUBLIC mingw32 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image SDL2_ttf obj)
endif(WIN32)

if(UNIX)
target_link_libraries(Character_Movement PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} SDL2_image::SDL2_image obj m)
endif(UNIX)