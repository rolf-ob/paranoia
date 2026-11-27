#include <iostream>
#include <stdexcept>

#include "game.h"
#include "graphics.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Game::Game() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    m_window = glfwCreateWindow(1440, 720, "Paranoia", nullptr, nullptr);
    if (m_window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGL()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    init_drawing();
}

Game::~Game() {
    cleanup_drawing();
    glfwTerminate();
}

void Game::run() {
    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();
        
        handle_input();
        update();
        draw();

        glfwSwapBuffers(m_window);
    }
}