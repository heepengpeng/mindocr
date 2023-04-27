#include "StringUtils.h"

std::vector<std::string> StringUtils::SplitString(std::string &input, char delim) {
    std::stringstream ss(input);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}
