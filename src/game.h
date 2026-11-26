#pragma once

#include <memory>

struct GLFWwindow;
class VertexBuffer;
class IndexBuffer;

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
    unsigned int m_vao = 0;
    std::unique_ptr<VertexBuffer> m_vb;
    std::unique_ptr<IndexBuffer>  m_ib;
    unsigned int m_shader_program;
    int m_color;
};