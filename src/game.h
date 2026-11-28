#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

class Renderer;
class Shader;
class Texture;
class VertexArray;
class VertexBuffer;
class IndexBuffer;

struct GLFWwindow;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void init_drawing();
    void cleanup_drawing();

    void handle_input();
    void update();
    void draw();

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Texture> m_texture;

    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;

    glm::mat4 m_proj;
    
    GLFWwindow* m_window = nullptr;
};