#include "game.h"
#include "graphics.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
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

    m_vb = std::make_unique<VertexBuffer>(positions, sizeof(positions));
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);

    m_ib = std::make_unique<IndexBuffer>(indices, 6);

    ShaderProgramSource source = parse_shader(RES_DIR "shaders/basic.shader");
    m_shader_program = create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(m_shader_program);

    m_color = glGetUniformLocation(m_shader_program, "u_color");
}

void Game::cleanup_drawing() {
    m_ib.reset();
    m_vb.reset();
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_shader_program);
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);
    
    glUniform4f(m_color, 0.0f, 0.0f, 1.0, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}