#include "game.h"
#include "graphics/renderer.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/vertex_array.h"
#include "graphics/vertex_buffer.h"
#include "graphics/vertex_buffer_layout.h"
#include "graphics/index_buffer.h"

void Game::init_drawing() {
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float positions[] = {
        -0.5, -0.5, 0.0f, 0.0f,
         0.5, -0.5, 1.0f, 0.0f,
         0.5,  0.5, 1.0f, 1.0f,
        -0.5,  0.5, 0.0f, 1.0f
    };

    unsigned int indices[] {
        0, 1, 2,
        2, 3, 0
    };

    m_renderer = std::make_unique<Renderer>();
    m_shader = std::make_unique<Shader>(RES_DIR "shaders/basic.shader");
    m_texture = std::make_unique<Texture>(RES_DIR "textures/catboom.png");
    m_va = std::make_unique<VertexArray>();
    m_vb = std::make_unique<VertexBuffer>(positions, sizeof(positions));
    VertexBufferLayout layout;

    layout.push<float>(2);
    layout.push<float>(2);
    m_va->add_buffer(*m_vb, layout);
    m_ib = std::make_unique<IndexBuffer>(indices, 6);
}

void Game::cleanup_drawing() {
    m_renderer.reset();
    m_shader.reset();
    m_texture.reset();
    m_va.reset();
    m_vb.reset();
    m_ib.reset();
}

void Game::draw() {
    m_renderer->clear();

    m_shader->bind();
    m_texture->bind();
    m_shader->set_uniform_1i("u_texture", 0);
    m_shader->set_uniform_4f("u_color", 1.0f, 1.0f, 1.0f, 0.5f);

    m_renderer->draw(*m_va, *m_ib, *m_shader);
}