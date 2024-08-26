#include "opengl/ShaderProgram.hpp"

#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "opengl/Shader.hpp"

namespace opengl
{
ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) : _handle {
    glCreateProgram()
}
{
    const auto vertexShader = std::make_unique<Shader>(_handle, GL_VERTEX_SHADER, vertexShaderSource);
    const auto fragmentShader = std::make_unique<Shader>(_handle, GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLint programLinked;

    glLinkProgram(_handle);
    glGetProgramiv(_handle, GL_LINK_STATUS, &programLinked);

    if (!programLinked)
    {
        std::string info(512, '\0');

        glGetProgramInfoLog(_handle, 512, nullptr, info.data());

        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED: " << info << std::endl;

        glDeleteProgram(_handle);
        throw std::runtime_error("Shader program linking failed");
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(_handle);
}

GLuint ShaderProgram::getHandle() const
{
    return _handle;
}

ShaderProgram& ShaderProgram::use()
{
    glUseProgram(_handle);

    return *this;
}

GLint ShaderProgram::getAttributeLocation(const std::string& name) const
{
    return glGetAttribLocation(_handle, name.c_str());
}

GLint ShaderProgram::getUniformLocation(const std::string& name) const
{
    return glGetUniformLocation(_handle, name.c_str());
}

ShaderProgram& ShaderProgram::setUniform1i(const std::string& name, const GLint v0)
{
    glUniform1i(getUniformLocation(name), v0);

    return *this;
}

ShaderProgram& ShaderProgram::setUniform1f(const std::string& name, const GLfloat v0)
{
    glUniform1f(getUniformLocation(name), v0);

    return *this;
}

ShaderProgram& ShaderProgram::setUniform3f(const std::string& name, const GLfloat v0, const GLfloat v1,
                                           const GLfloat v2)
{
    glUniform3f(getUniformLocation(name), v0, v1, v2);

    return *this;
}

ShaderProgram& ShaderProgram::setUniform4f(const std::string& name, const GLfloat v0, const GLfloat v1,
                                           const GLfloat v2, const GLfloat v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);

    return *this;
}

ShaderProgram& ShaderProgram::setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value_ptr(matrix));

    return *this;
}
}
