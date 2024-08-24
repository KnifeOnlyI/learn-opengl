#include <opengl/BufferObject.hpp>

#include "glad/glad.h"

namespace opengl {
BufferObject::BufferObject(const GLuint target) : _target {target} {
    glGenBuffers(1, &_handle);
}

BufferObject::~BufferObject() {
    glDeleteBuffers(1, &_handle);
}

unsigned BufferObject::getHandle() const {
    return _handle;
}

void BufferObject::use() const {
    glBindBuffer(_target, _handle);
}

void BufferObject::sendData(const void *data, const GLsizeiptr size, const GLenum usage) const {
    glBufferData(_target, size, data, usage);
}
}
