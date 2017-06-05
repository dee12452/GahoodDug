#include "../headers/GahoodFileUtil.hpp"

#include <SDL2/SDL.h>
#include <sstream>

std::vector<std::string> GahoodFileUtil::readFile(const std::string &file) {
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

std::vector<std::string> GahoodFileUtil::getWordsFromString(const std::string &line) {
    std::vector<std::string> words;
    std::string word;
    std::istringstream stream(line);
    while(stream >> word) {
        words.push_back(word);
    }
    return words;
}
