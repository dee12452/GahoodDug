#include "../headers/FileUtil.hpp"

#include <SDL2/SDL.h>
#include <sstream>
#include <dirent.h>
#include "../headers/Util.hpp"

FileUtil::FileUtil() {}

FileUtil::~FileUtil() {}

const uint8_t FileUtil::MAX_PATH_LENGTH = 255;

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

std::vector<std::string> FileUtil::getImageFiles(const char *path) {
    std::vector<std::string> files;
	char *folderPath = new char[MAX_PATH_LENGTH];
	strcpy(folderPath, path);
	recursiveSearchImages(files, folderPath, "");
	SDL_Log("Finished searching for images\n");
	delete[] folderPath;
	folderPath = NULL;
    return files;
}

void FileUtil::recursiveSearchImages(std::vector<std::string> &imageFiles, char *path, char *subDir) {
	DIR *dir;
	dir = opendir(path);
	if (dir != NULL) {
		dirent *fileName = readdir(dir);
		while (fileName != NULL) {
			if (isDirectory(fileName->d_name)) {
				//Recursive search into the directory
				char *folderPath = new char[MAX_PATH_LENGTH];
				strcpy(folderPath, path);
				strcat(folderPath, fileName->d_name);
				strcat(folderPath, "/");
				char newSubDir[MAX_PATH_LENGTH];
				strcpy(newSubDir, subDir);
				strcat(newSubDir, fileName->d_name);
				strcat(newSubDir, "/");
				recursiveSearchImages(imageFiles, folderPath, newSubDir);
				delete[] folderPath;
				folderPath = NULL;
			}
			else if(isFile(fileName->d_name)) {
				//Found an image, push it into the files vector
				SDL_Log("Found and pushed image: %s\n", fileName->d_name);
				imageFiles.push_back(subDir + std::string(fileName->d_name));
			}
			fileName = readdir(dir);
		}
		(void)closedir(dir);
	}
	else {
		std::string message = "Failed to find images in path: ";
		message += path;
		Util::fatalError(message.c_str());
	}
}

bool FileUtil::isDirectory(const char *f) {
	for (int i = 0; f[i] != '\0'; i++) {
		if (f[i] == '.')
			return false;
	}
	return true;
}

bool FileUtil::isFile(const char *f) {
	if (f[0] == '\0' || f[0] == '.') return false;
	return true;
}