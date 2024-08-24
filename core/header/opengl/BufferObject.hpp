#ifndef BUFFEROBJECT_HPP
#define BUFFEROBJECT_HPP
#include "OpenGLResource.hpp"
#include "glad/glad.h"

namespace opengl {
class BufferObject final : public OpenGLResource {
public:
    explicit BufferObject(GLuint target);

    ~BufferObject() override;

    [[nodiscard]] GLuint getHandle() const override;

    void sendData(const void *data, GLsizeiptr size, GLenum usage) const;

private:
    void bind() const;

    GLuint _target;
    GLuint _handle {};
};
}

#endif //BUFFEROBJECT_HPP
