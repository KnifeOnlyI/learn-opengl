#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP
#include <vector>

#include "OpenGLResource.hpp"
#include "Shader.hpp"

namespace opengl {
class ShaderProgram final : public OpenGLResource {
public:
    explicit ShaderProgram(const std::vector<Shader *> &shaders);

    ~ShaderProgram() override;

    [[nodiscard]] unsigned getHandle() const override;

    static void use(const ShaderProgram &shaderProgram);

private:
    unsigned int _handle;
};
}

#endif //SHADERPROGRAM_HPP
