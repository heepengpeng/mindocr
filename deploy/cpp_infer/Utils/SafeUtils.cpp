#include <memory>
#include "SafeUtils.h"

char *SafeUtils::ReadFile(const char *fileName, size_t *size) {
    if (fileName == nullptr) {
        std::cerr << "file is nullptr" << std::endl;
        return nullptr;
    }

    std::ifstream ifs(fileName, std::ifstream::in | std::ifstream::binary);

    if (!ifs.good()) {
        std::cerr << "file: " << fileName << "is not exist." << std::endl;
        return nullptr;
    }

    if (!ifs.is_open()) {
        std::cerr << "file: " << fileName << "open failed." << std::endl;
        return nullptr;
    }

    ifs.seekg(0, std::ios::end);

    *size = ifs.tellg();

    std::unique_ptr<char[]> buf(new(std::nothrow) char[*size]);
    if (buf == nullptr) {
        std::cerr << "malloc buf failed, file: " << fileName << std::endl;
        ifs.close();
        return nullptr;
    }

    ifs.seekg(0, std::ios::beg);
    ifs.read(buf.get(), *size);
    ifs.close();
    return buf.release();
}
