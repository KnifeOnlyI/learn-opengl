#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>

#include "OpenGLResource.hpp"

namespace opengl
{
class Texture final : public OpenGLResource
{
public:
    explicit Texture(GLuint target, const std::string& filepath, GLenum format, GLint wrapping, GLint filtering);

    ~Texture() override;

    [[nodiscard]] GLuint getHandle() const override;

    void bind() const;

    void setActive(GLenum textureUnit) const;

private:
    GLuint _target {};
    GLuint _handle {};
};
}

#endif //TEXTURE_HPP
