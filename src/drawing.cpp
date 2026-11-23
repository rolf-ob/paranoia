#include "graphics.h"
#include "shaders.h"

static GLuint vao;
static GLuint vbo;
static GLuint shader_program;

void init_drawing() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    float positions[6] = {
        -0.5f,  0.5f,
         0.0f, -0.5f,
         0.5f,  0.5f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

    ShaderProgramSource source = parse_shader("res/shaders/basic.shader");
    shader_program = create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(shader_program);
}

void draw(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
}

void cleanup_drawing() {
    glDeleteProgram(shader_program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}