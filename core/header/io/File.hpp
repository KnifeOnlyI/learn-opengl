#ifndef FILE_HPP
#define FILE_HPP
#include <fstream>

namespace io {
class File final {
public:
    explicit File(const std::string &path);

    std::string getContent() const;

    ~File();

private:
    std::ifstream _file;

    std::string _content;
};
}

#endif //FILE_HPP
