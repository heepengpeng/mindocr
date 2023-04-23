
#ifndef SAFE_UTILS_H
#define SAFE_UTILS_H


class SafeUtils {
public:
    static checkValidFile(const string &path, const string & name);
    static char* ReadFile(const char *file, size_t *size);
};


#endif
