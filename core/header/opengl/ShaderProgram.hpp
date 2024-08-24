#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <vector>

#include "OpenGLResource.hpp"
#include "Shader.hpp"

namespace opengl {
class ShaderProgram final : public OpenGLResource {
public:

    static void use(const ShaderProgram &shaderProgram);

    explicit ShaderProgram(const std::vector<Shader *> &shaders);

    ~ShaderProgram() override;

    [[nodiscard]] unsigned getHandle() const override;

    GLint getAttributeLocation(const std::string &name) const;

    GLint getUniformLocation(const std::string &name) const;

private:
    unsigned int _handle;
};
}

#endif //SHADERPROGRAM_HPP
