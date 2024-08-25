#include "opengl/Texture.hpp"

#include <memory>

#include "sdl/Image.hpp"

namespace opengl
{
Texture::Texture(const GLuint target, const std::string& filepath): _target {target}
{
    glGenTextures(1, &_handle);

    glBindTexture(_target, _handle);

    glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const auto textureImage = std::make_unique<sdl::Image>(filepath);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        textureImage->getWidth(),
        textureImage->getHeight(),
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureImage->getPixels()
    );

    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_handle);
}

GLuint Texture::getHandle() const
{
    return _handle;
}

void Texture::bind() const
{
    glBindTexture(_target, _handle);
}

void Texture::setActive(const GLenum textureUnit) const
{
    glActiveTexture(textureUnit);
    bind();
}
}
