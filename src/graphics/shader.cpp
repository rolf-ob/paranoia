#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "graphics.h"
#include "shader.h"

Shader::Shader(const std::string& filepath) : m_filepath(filepath) {
    ShaderProgramSource source = parse_shader(filepath);
    m_renderer_id = create_shader(source.vertex_source, source.fragment_source);
}

Shader::~Shader() {
    glDeleteProgram(m_renderer_id);
}

ShaderProgramSource Shader::parse_shader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (!stream.is_open())
        throw std::runtime_error("Could not open shader file: " + filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        glDeleteShader(id);
        throw std::runtime_error(
            std::string("Failed to compile ") +
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") +
            std::string(" shader!\n") +
            message
        );
    }
    
    return id;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::bind() const {
    glUseProgram(m_renderer_id);
}

void Shader::unbind() const {
    glUseProgram(0);
}

void Shader::set_uniform_1i(const std::string &name, int value) {
    glUniform1i(get_uniform_location(name), value);
}

void Shader::set_uniform_1f(const std::string &name, float value) {
    glUniform1f(get_uniform_location(name), value);
}

void Shader::set_uniform_4f(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(get_uniform_location(name), v0, v1, v2, v3);
}

int Shader::get_uniform_location(const std::string& name) {
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];

    int location = glGetUniformLocation(m_renderer_id, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    
    m_uniform_location_cache[name] = location;
    return location;
}