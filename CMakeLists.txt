cmake_minimum_required(VERSION 3.14)
project(Paranoia)

set(CMAKE_CXX_STANDARD 17)

# Find system OpenGL
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
add_executable(OpenGL src/main.cpp src/glad.c
    src/drawing.cpp
    src/input.cpp
    src/graphics.h
    src/initialization.cpp
    src/shaders.cpp
    src/shaders.h)

target_include_directories(OpenGL PRIVATE include)

# Link GLFW and OpenGL to your project
target_link_libraries(OpenGL PRIVATE glfw OpenGL::GL)