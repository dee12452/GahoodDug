#include "../headers/Util.hpp"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_error.h>
#include <chrono>

void Util::fatalError(const char *message) {
    SDL_Log("Fatal Error: %s\n", message);
    exit(EXIT_FAILURE);
}

void Util::fatalSDLError(const char *message) {
    SDL_Log("Fatal SDL Error: %s\n%s\n", message, SDL_GetError());
    exit(EXIT_FAILURE);
}

void Util::log(const std::string &message) {
    SDL_Log("%s\n", message.c_str());
}

__int64 Util::getCurrentTimeMillis() {
	std::chrono::milliseconds currMS = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now().time_since_epoch());
	return currMS.count();
}
