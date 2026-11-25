#include "game.h"
#include "graphics.h"
#include "shaders.h"

void Game::init_drawing() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    float positions[8] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.5,  0.5,
        -0.5,  0.5,
    };

    unsigned int indices[6] {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    ShaderProgramSource source = parse_shader(RES_DIR "shaders/basic.shader");
    m_shader_program = create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(m_shader_program);
}

void Game::cleanup_drawing() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    glDeleteProgram(m_shader_program);
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}