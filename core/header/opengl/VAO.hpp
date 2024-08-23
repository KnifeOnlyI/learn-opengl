#ifndef VAO_HPP
#define VAO_HPP
#include "OpenGLResource.hpp"

namespace opengl {
class VAO final : public OpenGLResource {
public:
    VAO();

    ~VAO() override;

    [[nodiscard]] unsigned getHandle() const override;

    static void bind(const VAO &vao);

private:
    unsigned int _handle {};
};
}

#endif //VAO_HPP
