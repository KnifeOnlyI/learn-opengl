#include "stb/Image.hpp"

#include <iostream>
#include <stdexcept>

#include "stb/stb_image.h"

namespace stb
{
void Image::flipVerticallyOnLoad(const bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
}

Image::Image(const std::string& path)
{
    _handle = stbi_load(path.c_str(), &_width, &_height, &_nrChannels, 0);

    if (_handle == nullptr)
    {
        std::cerr << "Failed to load image : " << path << std::endl;

        throw std::runtime_error("Failed to load image");
    }
}

Image::~Image()
{
    stbi_image_free(_handle);
}

unsigned char* Image::getHandle() const
{
    return _handle;
}

int Image::getWidth() const
{
    return _width;
}

int Image::getHeight() const
{
    return _height;
}
}
