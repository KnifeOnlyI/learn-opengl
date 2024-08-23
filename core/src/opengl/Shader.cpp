#include <iostream>

#include "opengl/Shader.hpp"

namespace opengl {
Shader::Shader(const std::string &source, const GLenum type): _handle {glCreateShader(type)} {
    const char *shaderSourceCode = source.c_str();

    glShaderSource(_handle, 1, &shaderSourceCode, nullptr);
    glCompileShader(_handle);

    int success;

    glGetShaderiv(_handle, GL_COMPILE_STATUS, &success);

    if (!success) {
        std::string info(512, '\0');

        glGetShaderInfoLog(_handle, 512, nullptr, info.data());

        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
    }
}

Shader::~Shader() {
    glDeleteShader(_handle);
}

unsigned Shader::getHandle() const {
    return _handle;
}
}
