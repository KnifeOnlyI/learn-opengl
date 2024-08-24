#include "opengl/VAO.hpp"

#include "glad/glad.h"

namespace opengl {
void VAO::bind(const VAO &vao) {
    glBindVertexArray(vao.getHandle());
}

VAO::VAO() {
    glGenVertexArrays(1, &_handle);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &_handle);
}

unsigned VAO::getHandle() const {
    return _handle;
}
}
