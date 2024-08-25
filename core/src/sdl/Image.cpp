#include "sdl/Image.hpp"

#include <iostream>
#include <SDL_image.h>
#include <stdexcept>

namespace sdl {
Image::Image(const std::string &path) {
    _handle = IMG_Load(path.c_str());

    if (_handle == nullptr) {
        std::cerr << "Failed to load image '" << path << "': " << IMG_GetError() << std::endl;
        throw std::runtime_error("Failed to load image");
    }
}

Image::~Image() {
    SDL_FreeSurface(_handle);
}

void *Image::getPixels() const {
    return _handle->pixels;
}

int Image::getWidth() const {
    return _handle->w;
}

int Image::getHeight() const {
    return _handle->h;
}
}
