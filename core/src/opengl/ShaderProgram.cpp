#include <iostream>

#include "opengl/ShaderProgram.hpp"

#include "glad/glad.h"

namespace opengl {
ShaderProgram::ShaderProgram(const std::vector<Shader *> &shaders): _handle {glCreateProgram()} {
    int success;

    if (!_handle) {
        std::cerr << "ERROR::SHADER::PROGRAM::CREATION_FAILED: " << glGetError() << std::endl;
    }

    // For each shaders in the vector, attach it to the program
    for (const auto &shader: shaders) {
        glAttachShader(_handle, shader->getHandle());
        glGetProgramiv(_handle, GL_ATTACHED_SHADERS, &success);

        if (!success) {
            std::string info(512, '\0');

            glGetShaderInfoLog(_handle, 512, nullptr, info.data());

            std::cerr << "ERROR::SHADER::PROGRAM::ATTACH_FAILED: " << info << std::endl;
        }
    }

    glLinkProgram(_handle);
    glGetProgramiv(_handle, GL_LINK_STATUS, &success);

    if (!success) {
        std::string info(512, '\0');

        glGetProgramInfoLog(_handle, 512, nullptr, info.data());

        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_handle);
}

unsigned ShaderProgram::getHandle() const {
    return _handle;
}

GLint ShaderProgram::getAttributeLocation(const std::string &name) const {
    return glGetAttribLocation(_handle, name.c_str());
}

void ShaderProgram::use(const ShaderProgram &shaderProgram) {
    glUseProgram(shaderProgram.getHandle());
}
}
