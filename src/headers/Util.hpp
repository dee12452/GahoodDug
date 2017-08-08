#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

class Util {
public:
    static void fatalError(const char *);
    static void fatalSDLError(const char *);
    static void log(const std::string &);
	static unsigned int getCurrentTimeMillis();
private:
    Util() {}
    ~Util() {}
};

#endif
