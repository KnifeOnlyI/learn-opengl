#ifndef VAO_HPP
#define VAO_HPP
#include "OpenGLResource.hpp"

namespace opengl {
class VAO final : public OpenGLResource {
public:

    VAO();

    ~VAO() override;

    [[nodiscard]] GLuint getHandle() const override;

    void use() const;

private:
    GLuint _handle {};
};
}

#endif //VAO_HPP
