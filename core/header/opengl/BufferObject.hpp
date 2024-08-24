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

    void sendData(const void *data, GLsizeiptr size, GLenum usage) const;

private:
    void bind() const;

    GLuint _target;
    unsigned int _handle {};
};
}

#endif //VBO_HPP
