#include "../headers/GahoodUtil.hpp"

#include <iostream>
#include <SDL2/SDL.h>

void GahoodUtil::fatalError(const std::string &msg) {
    std::cout << "ERROR: " << std::endl
        << msg << std::endl;
    exit(EXIT_FAILURE);
}

void GahoodUtil::fatalSDLError(const std::string &msg) {
    std::cout << "SDL ERROR: " << std::endl
        << msg << std::endl
        << std::string(SDL_GetError()) << std::endl;
    exit(EXIT_FAILURE);
}
