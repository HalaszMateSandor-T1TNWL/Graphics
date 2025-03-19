cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Line)


add_executable(Line src/main.c)
target_include_directories(Line PRIVATE include)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

if(WIN32)
target_link_libraries(Line PUBLIC mingw32 ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
endif(WIN32)

if(UNIX)
target_link_libraries(Line PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
endif(UNIX)