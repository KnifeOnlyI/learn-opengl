#include "opengl/Shader.hpp"

#include <iostream>
#include <ostream>

namespace opengl
{
    Shader::Shader(const GLuint shaderProgram, const GLenum type, const std::string& source): _handle{
        glCreateShader(type)
    }
    {
        const char* cSource = source.c_str();

        glShaderSource(_handle, 1, &cSource, nullptr);
        glCompileShader(_handle);

        GLint shaderCompiled;

        glGetShaderiv(_handle, GL_COMPILE_STATUS, &shaderCompiled);

        if (!shaderCompiled)
        {
            std::string info(512, '\0');

            glGetShaderInfoLog(_handle, 512, nullptr, info.data());

            std::cerr << "ERROR::SHADER::"
                << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                << "::COMPILATION_FAILED\n" << info << std::endl;

            glDeleteShader(_handle);
            throw std::runtime_error("Shader compilation failed");
        }

        GLint shaderAttached;

        glAttachShader(shaderProgram, _handle);
        glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &shaderAttached);

        if (!shaderAttached)
        {
            std::string info(512, '\0');

            glGetShaderInfoLog(_handle, 512, nullptr, info.data());

            std::cerr << "ERROR::SHADER::VERTEX::ATTACH_TO_PROGRAM_FAILED: " << info << std::endl;

            glDeleteShader(_handle);
            throw std::runtime_error("Shader attach failed");
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(_handle);
    }

    GLuint Shader::getHandle() const
    {
        return _handle;
    }
}
