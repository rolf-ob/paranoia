#include "graphics.h"

void draw(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}