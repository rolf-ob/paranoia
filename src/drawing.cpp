#include "game.h"
#include "graphics.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
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

    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.push<float>(2);
    m_va->add_buffer(*m_vb, layout);

    m_ib = std::make_unique<IndexBuffer>(indices, 6);

    ShaderProgramSource source = parse_shader(RES_DIR "shaders/basic.shader");
    m_shader_program = create_shader(source.vertex_source, source.fragment_source);
    glUseProgram(m_shader_program);

    m_color = glGetUniformLocation(m_shader_program, "u_color");
}

void Game::cleanup_drawing() {
    m_ib.reset();
    m_vb.reset();
    m_va.reset();
    glDeleteProgram(m_shader_program);
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_va->bind();
    
    glUniform4f(m_color, 0.0f, 0.0f, 1.0, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}