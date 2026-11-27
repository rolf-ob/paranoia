#pragma once

#include <memory>

struct GLFWwindow;
class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;

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

    GLFWwindow* m_window = nullptr;
    std::unique_ptr<VertexArray> m_va;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer> m_ib;
    std::unique_ptr<Shader> m_shader;
    
};