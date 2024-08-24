#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP
#include <string>

#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl {
class ShaderProgram final : public OpenGLResource {
public:
    ShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

    ~ShaderProgram() override;

    [[nodiscard]] GLuint getHandle() const override;

    GLint getAttributeLocation(const std::string &name) const;

    GLint getUniformLocation(const std::string &name) const;

    ShaderProgram &use();

    ShaderProgram &setUniform3f(const std::string &name, float v0, float v1, float v2);

    ShaderProgram &setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

private:
    GLuint _handle {};
};
}

#endif //SHADER_PROGRAM_HPP
