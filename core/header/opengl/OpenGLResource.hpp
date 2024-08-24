#ifndef OPENGLRESOURCE_HPP
#define OPENGLRESOURCE_HPP
#include "glad/glad.h"

namespace opengl {
class OpenGLResource {
public:
    virtual ~OpenGLResource() = default;

    [[nodiscard]] virtual GLuint getHandle() const = 0;
};
}

#endif //OPENGLRESOURCE_HPP
