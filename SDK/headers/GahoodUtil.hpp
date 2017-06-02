#ifndef GAHOOD_UTIL_HPP
#define GAHOOD_UTIL_HPP

#include <string>

class GahoodUtil {
public:
    static void fatalError(const std::string &);
    static void fatalSDLError(const std::string &);
private:
    GahoodUtil() {}
    ~GahoodUtil() {}
};

#endif
