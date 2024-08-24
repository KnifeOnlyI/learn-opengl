#ifndef VBO_HPP
#define VBO_HPP
#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl {
class BufferObject final : public OpenGLResource {
public:
    explicit BufferObject(GLuint target);

    ~BufferObject() override;

    [[nodiscard]] unsigned getHandle() const override;

    void use() const;

    void sendData(const void *data, GLsizeiptr size, GLenum usage) const;

private:
    GLuint _target;
    unsigned int _handle {};
};
}

#endif //VBO_HPP
