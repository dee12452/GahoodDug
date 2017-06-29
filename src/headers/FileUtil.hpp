#ifndef GAHOOD_FILE_UTIL_HPP
#define GAHOOD_FILE_UTIL_HPP

#include <vector>
#include <string>

class FileUtil {
public:
    static std::vector<std::string> readFile(const std::string &);
    static std::vector<std::string> getWordsFromString(const std::string &);
    static std::vector<std::string> getImageFiles(const char *);

private:
    FileUtil();
    ~FileUtil();
};

#endif
