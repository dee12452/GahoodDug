#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

class Util {
public:
    static void fatalError(const char *errMessage);
    static void fatalSDLError(const char *errMessage);
    static void log(const std::string &message);
	static void print(const std::string &message);
	static int64_t getCurrentTimeMillis();
private:
    Util() {}
    ~Util() {}
};

#endif
