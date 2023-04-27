
#ifndef SAFE_UTILS_H
#define SAFE_UTILS_H
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

class SafeUtils {
public:
//    static checkValidFile(const string &path, const string & name);
    static char* ReadFile(const char *fileName, size_t *size);
};


#endif
