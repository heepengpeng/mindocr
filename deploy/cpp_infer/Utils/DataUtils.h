//
// Created by XIANAI on 2023/4/25.
//
#include <cstdint>
#ifndef DATA_UTILS_H
#define DATA_UTILS_H
class __attribute__((visibility("defalut"))) ResizedImageInfo {
public:
    uint32_t widthResize;
    uint32_t heightResize;
    uint32_t widthOriginal;
    uint32_t heightOriginal;
    float ratio;
};
#endif
