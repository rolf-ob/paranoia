#include "graphics.h"

GLFWwindow* initialize();
void handle_input(GLFWwindow* window);
void draw(GLFWwindow* window);
void init_drawing();

int main() {
    GLFWwindow* window = initialize();
    if (!window) {
        return -1;
    }

    init_drawing();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        handle_input(window);
        draw(window);
    }
    glfwTerminate();
}