#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SDL_surface.h>
#include <string>

namespace sdl {
class Image {
public:

    explicit Image(const std::string &path);

    ~Image();

    [[nodiscard]] void *getPixels() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

private:

    SDL_Surface *_handle;
};
}

#endif //IMAGE_HPP
