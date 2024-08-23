#ifndef OPENGLRESOURCE_HPP
#define OPENGLRESOURCE_HPP

namespace opengl {
class OpenGLResource {
public:
    virtual ~OpenGLResource() = default;

    [[nodiscard]] virtual unsigned int getHandle() const = 0;
};
}

#endif //OPENGLRESOURCE_HPP
