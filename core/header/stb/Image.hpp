#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <string>

namespace stb
{
class Image
{
public:
    static void flipVerticallyOnLoad(bool flip);

    explicit Image(const std::string& path);

    ~Image();

    [[nodiscard]] unsigned char* getHandle() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

private:
    int _width {};
    int _height {};
    int _nrChannels {};
    unsigned char* _handle {};
};
}

#endif //IMAGE_HPP
