#pragma once

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

    GLFWwindow* m_window;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ibo;
    unsigned int m_shader_program;
};