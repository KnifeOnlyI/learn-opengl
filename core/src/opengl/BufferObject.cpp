#include <opengl/BufferObject.hpp>

#include "glad/glad.h"

namespace opengl {
BufferObject::BufferObject(const GLuint target) : _target {target} {
    glGenBuffers(1, &_handle);
}

BufferObject::~BufferObject() {
    glDeleteBuffers(1, &_handle);
}

GLuint BufferObject::getHandle() const {
    return _handle;
}

void BufferObject::sendData(const void *data, const GLsizeiptr size, const GLenum usage) const {
    bind();
    glBufferData(_target, size, data, usage);
}

void BufferObject::bind() const {
    glBindBuffer(_target, _handle);
}
}
