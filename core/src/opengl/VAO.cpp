#include "opengl/VAO.hpp"

#include "glad/glad.h"

namespace opengl {
VAO::VAO() {
    glGenVertexArrays(1, &_handle);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &_handle);
}

GLuint VAO::getHandle() const {
    return _handle;
}

void VAO::use() const {
    glBindVertexArray(_handle);
}
}
