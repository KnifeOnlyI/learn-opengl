#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>

#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl {
class Shader final : public OpenGLResource {
public:
    Shader(const std::string &source, GLenum type);

    ~Shader() override;

    [[nodiscard]] unsigned getHandle() const override;

private:
    unsigned int _handle;
};
}

#endif //SHADER_HPP
