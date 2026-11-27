#include "game.h"
#include "graphics.h"
#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"
#include "graphics/vertex_buffer_layout.h"
#include "graphics/index_buffer.h"
#include "graphics/shader.h"

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

    m_shader = std::make_unique<Shader>(RES_DIR "shaders/basic.shader");
    m_shader->bind();
}

void Game::cleanup_drawing() {
    m_ib.reset();
    m_vb.reset();
    m_va.reset();
    m_shader.reset();
}

void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    m_va->bind();
    m_shader->set_uniform_4f("u_color", 0.0f, 0.0f, 1.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}