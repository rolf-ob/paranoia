#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};

class Shader {
private:
    std::string m_filepath;
    unsigned int m_renderer_id;
    std::unordered_map<std::string, int> m_uniform_location_cache;

public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void set_uniform_1i(const std::string& name, int value);
    void set_uniform_1f(const std::string& name, float value);
    void set_uniform_4f(const std::string& name, float v0, float v1, float f3, float f4);

private:
    ShaderProgramSource parse_shader(const std::string& filepath);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);

    int get_uniform_location(const std::string& name);
};