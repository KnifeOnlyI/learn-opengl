#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>

#include "OpenGLResource.hpp"

namespace opengl {
class Shader final : public OpenGLResource {
public:
    Shader(GLuint shaderProgram, GLenum type, const std::string &source);

    ~Shader() override;

    [[nodiscard]] GLuint getHandle() const override;

private:
    GLuint _handle {};
};
}

#endif //SHADER_HPP
