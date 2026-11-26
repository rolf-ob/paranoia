cmake_minimum_required(VERSION 3.14)
project(Paranoia)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

add_executable(OpenGL include/glad.c
    src/main.cpp
    src/game.cpp
    src/input.cpp
    src/physics.cpp
    src/drawing.cpp
    src/shaders.cpp
    src/vertex_buffer.cpp
    src/index_buffer.cpp
)

target_include_directories(OpenGL PRIVATE src include)

target_link_libraries(OpenGL PRIVATE glfw OpenGL::GL)

target_compile_definitions(OpenGL PRIVATE RES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/res/")