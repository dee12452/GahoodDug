#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

class Util {
public:
    static void fatalError(const char *);
    static void fatalSDLError(const char *);
    static void log(const std::string &);
	static void print(const std::string &);
	static int64_t getCurrentTimeMillis();
private:
    Util() {}
    ~Util() {}
};

#endif
