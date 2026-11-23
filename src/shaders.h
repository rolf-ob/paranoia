#pragma once
#include <string>

struct ShaderProgramSource {
    std::string vertex_source;
    std::string fragment_source;
};

ShaderProgramSource parse_shader(const std::string& filepath);
unsigned int create_shader(const std::string& vertex, const std::string& fragment);