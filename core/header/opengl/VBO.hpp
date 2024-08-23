#ifndef VBO_HPP
#define VBO_HPP
#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl {
class VBO final : public OpenGLResource {
public:
    explicit VBO(GLuint target = GL_ARRAY_BUFFER);

    ~VBO() override;

    [[nodiscard]] unsigned getHandle() const override;

    void use() const;

    void sendData(const void *data, GLsizeiptr size, GLenum usage) const;

private:
    GLuint _target {GL_ARRAY_BUFFER};
    unsigned int _handle {};
};
}

#endif //VBO_HPP
