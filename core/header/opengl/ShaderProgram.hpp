#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP
#include <string>

#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl
{
class ShaderProgram final : public OpenGLResource
{
public:
    ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    ~ShaderProgram() override;

    [[nodiscard]] GLuint getHandle() const override;

    [[nodiscard]] GLint getAttributeLocation(const std::string& name) const;

    [[nodiscard]] GLint getUniformLocation(const std::string& name) const;

    ShaderProgram& use();

    ShaderProgram& setUniform1i(const std::string& name, GLint v0);

    ShaderProgram& setUniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);

    ShaderProgram& setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

private:
    GLuint _handle {};
};
}

#endif //SHADER_PROGRAM_HPP
