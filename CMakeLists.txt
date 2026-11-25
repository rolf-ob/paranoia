cmake_minimum_required(VERSION 3.14)
project(Paranoia)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

# Automatically fetch and build GLFW
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# Add your executable target (compiling main.cpp and glad.c together)
add_executable(OpenGL include/glad.c
    src/main.cpp
    src/game.cpp
    src/input.cpp
    src/drawing.cpp
    src/shaders.cpp
)

target_include_directories(OpenGL PRIVATE src include)

# Link GLFW and OpenGL to your project
target_link_libraries(OpenGL PRIVATE glfw OpenGL::GL)

target_compile_definitions(OpenGL PRIVATE RES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/res/")