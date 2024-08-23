#include <io/File.hpp>

namespace io {
File::File(const std::string &path): _file {std::ifstream(path)},
                                     _content {(std::istreambuf_iterator(_file)), (std::istreambuf_iterator<char>())} {
}

std::string File::getContent() const {
    return _content;
}

File::~File() {
    _file.close();
}
}
