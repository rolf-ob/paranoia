#include "graphics.h"

GLFWwindow* initialize();
void handle_input(GLFWwindow* window);
void draw(GLFWwindow* window);

int main() {
    GLFWwindow* window = initialize();
    if (!window) {
        return -1;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        handle_input(window);
        draw(window);
    }
    glfwTerminate();
}