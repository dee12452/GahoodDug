#include "../headers/FileUtil.hpp"

#include <SDL2/SDL.h>
#include <sstream>
#include <dirent.h>
#include "../headers/Util.hpp"

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
    DIR *dir;
    dir = opendir(path);
    if(dir != NULL) {
        dirent *fileName = readdir(dir);
        while(fileName != NULL) {
            files.push_back(std::string(fileName->d_name));
            fileName = readdir(dir);
        }
        (void) closedir(dir);
    }
    else {
        std::string message = "Failed to find images in path: ";
        message += path;
        Util::fatalError(message.c_str());
    }
    return files;
}
