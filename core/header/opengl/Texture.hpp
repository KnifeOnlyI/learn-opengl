#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>

#include "OpenGLResource.hpp"

namespace opengl
{
class Texture final : public OpenGLResource
{
public:
    explicit Texture(GLuint target, const std::string& filepath);

    ~Texture() override;

    [[nodiscard]] GLuint getHandle() const override;

    void bind() const;

private:
    GLuint _target {};
    GLuint _handle {};
};
}

#endif //TEXTURE_HPP
