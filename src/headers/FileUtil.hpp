#ifndef GAHOOD_FILE_UTIL_HPP
#define GAHOOD_FILE_UTIL_HPP

#include <vector>
#include <string>
#include <stdint.h>

class FileUtil {
public:
    static std::vector<std::string> readFile(const std::string &);
    static std::vector<std::string> getWordsFromString(const std::string &);
    static std::vector<std::string> getImageFiles(const char *);

private:
	static const uint8_t MAX_PATH_LENGTH;
	static bool isDirectory(const char *);
	static bool isFile(const char *);
	static void recursiveSearchImages(std::vector<std::string> &, char *, char *subDir);
    FileUtil();
    ~FileUtil();
};

#endif
