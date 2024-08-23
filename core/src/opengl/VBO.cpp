#include <opengl/VBO.hpp>

#include "glad/glad.h"

namespace opengl {
VBO::VBO(const GLuint target) : _target {target} {
    glGenBuffers(1, &_handle);
}

VBO::~VBO() {
    glDeleteBuffers(1, &_handle);
}

unsigned VBO::getHandle() const {
    return _handle;
}

void VBO::use() const {
    glBindBuffer(_target, _handle);
}

void VBO::sendData(const void *data, const GLsizeiptr size, const GLenum usage) const {
    glBufferData(_target, size, data, usage);
}
}
