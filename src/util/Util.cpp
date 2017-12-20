#include "Util.hpp"
#include <thread>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "../sprite/Sprite.hpp"
#include "Constants.hpp"

void Util::fatalError(const char *message) {
	log(SDL_LOG_PRIORITY_CRITICAL, message);
    exit(EXIT_FAILURE);
}

void Util::fatalSDLError(const char *message) {
	log(SDL_LOG_PRIORITY_CRITICAL, std::string(message) + "\n" + SDL_GetError());
    exit(EXIT_FAILURE);
}

void Util::log(const std::string &message) { log(SDL_LOG_PRIORITY_INFO, message); }

void Util::log(const SDL_LogPriority &priority, const std::string &message) {
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, priority, message.c_str());
}

void Util::sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

SDL_Color Util::createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_Color color;
    color.r = r; color.g = g; color.b = b; color.a = a;
    return color;
}

SDL_Rect Util::createRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x; rect.y = y; rect.w = w; rect.h = h;
    return rect;
}

SDL_Rect Util::createRectCentered(int w, int h) {
    return createRect(Constants::WINDOW_WIDTH / 2 - w / 2, 
            Constants::WINDOW_HEIGHT / 2 - h / 2, w, h);
}

SDL_Rect Util::createRectCenteredVertically(int x, int w, int h) {
    return createRect(x, Constants::WINDOW_HEIGHT / 2 - h / 2, w, h);
}

SDL_Rect Util::createRectCenteredHorizontally(int y, int w, int h) {
    return createRect(Constants::WINDOW_WIDTH / 2 - w / 2, y, w, h);
}

void Util::querySpriteSourceImage(Sprite *sprite, int &w, int &h) {
	if (SDL_QueryTexture(sprite->getTexture(), NULL, NULL, &w, &h) != 0) {
		Util::fatalSDLError("Failed to query texture");
	}
}
