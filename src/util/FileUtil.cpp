#include "FileUtil.hpp"

#include <SDL2/SDL.h>
#include <sstream>
#include <dirent.h>
#include "Util.hpp"

FileUtil::FileUtil() {}

FileUtil::~FileUtil() {}

const uint16_t FileUtil::MAX_PATH_LENGTH = 2500;

std::vector<std::string> FileUtil::readFile(const std::string &file) {
    std::vector<std::string> lines;
    SDL_RWops *ctx = SDL_RWFromFile(file.c_str(), "rb");
    if(ctx != NULL) {
        std::string line = "";
        char buffer[2];
        buffer[1] = '\0';
        while(SDL_RWread(ctx, buffer, sizeof(char), 1) != 0) {
            if(buffer[0] == '\n' || buffer[0] == '\0' || buffer[0] == EOF) {
                lines.push_back(line);
                line = "";
                memset(buffer, 0, sizeof(buffer));
                buffer[1] = '\0';
            }
            else {
                line += buffer[0];
                memset(buffer, 0, sizeof(buffer));
                buffer[1] = '\0';
            }
        }
        SDL_RWclose(ctx);
        ctx = NULL;
    }
    return lines;
}

std::vector<std::string> FileUtil::getWordsFromString(const std::string &line) {
    std::vector<std::string> words;
    std::string word;
    std::istringstream stream(line);
    while(stream >> word) {
        words.push_back(word);
    }
    return words;
}

std::vector<std::string> FileUtil::getFilesRecursively(const char *folderPath, const char *fileExtension) {
    std::vector<std::string> files;
    char *path = new char[MAX_PATH_LENGTH];
    strcpy(path, folderPath);
	recursiveSearchFiles(files, path, fileExtension);
	delete[] path;
    path = NULL;
    return files;
}

void FileUtil::recursiveSearchFiles(std::vector<std::string> &files, char *path, const char *fileExtension) {
	DIR *dir;
	dir = opendir(path);
	if (dir != NULL) {
		dirent *fileName = readdir(dir);
		while (fileName != NULL) {
			if (isDirectory(fileName->d_name)) {
				//Recursive search into the directory
				char *newPath = new char[MAX_PATH_LENGTH];
                strcpy(newPath, path);
                strcat(newPath, "/");
                strcat(newPath, fileName->d_name);
				recursiveSearchFiles(files, newPath, fileExtension);
                delete[] newPath;
			}
			else {
				//Found a file matching the extension, push it into the files vector
				if(isCorrectExtension(fileName->d_name, fileExtension)) {
                    std::string filePath(path);
                    files.push_back(filePath + "/" + std::string(fileName->d_name));
			    }
            }
			fileName = readdir(dir);
		}
		(void)closedir(dir);
	}
	else {
		std::string message = "Failed to find files in path: ";
		message += path;
		Util::fatalError(message.c_str());
	}
}

bool FileUtil::isCorrectExtension(char *file, const char *fileExtension) {
    int i = 0, j = 0;
    while(file[i] != '.') i++;
    while(file[i] == fileExtension[j]) {
        i++; j++;
        if(file[i] == '\0' || fileExtension[j] == '\0') {
            break;
        }
    }
    return file[i] == fileExtension[j];
}

bool FileUtil::isDirectory(const char *f) {
	for (int i = 0; f[i] != '\0'; i++) {
		if (f[i] == '.') {
			return false;
        }
    }
	return true;
}

std::string FileUtil::getFileName(const char *pathToFile) {
    std::string fileName = "";
    int length = 0;
    while(pathToFile[length] != '\0') length++;
    length--;
    while(pathToFile[length] != '/' 
            && pathToFile[length] != '\\'
            && length >= 0) {
        fileName = pathToFile[length] + fileName;
        length--;
    }
    return fileName;
}
