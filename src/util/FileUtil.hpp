#ifndef GAHOOD_FILE_UTIL_HPP
#define GAHOOD_FILE_UTIL_HPP

#include <vector>
#include <string>
#include <stdint.h>

class FileUtil {
public:
    /* Read a file and return it as a vector of strings, line by line */
    static std::vector<std::string> readFile(const std::string &fileName);
    
    /* Read a 'line' and return the words (separated by spaces) */
    static std::vector<std::string> getWordsFromString(const std::string &str);

    /* Recursively search through a directory for files that match the fileExtension parameter (ie: ".png", ".json")
     * NOTE: FAILS when the function runs into a file without an extension (ie: application binaries in Linux like 'gradlew') */
    static std::vector<std::string> getFilesRecursively(const char *folderPath, const char *fileExtension);

    /* Get a file's name from the path to the file
     * (ie: "/folder1/folder2/folder3/file.png" will be turned into just "file.png") */
    static std::string getFileName(const char *filePath);

private:
	static const uint16_t MAX_PATH_LENGTH;
	static bool isDirectory(const char *path);
    static bool isCorrectExtension(char *file, const char *fileExtension);
	static void recursiveSearchFiles(std::vector<std::string> &files, char *folderPath, const char *fileExtension);
    FileUtil();
    ~FileUtil();
};

#endif
