#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <stdint.h>
#include <SDL2/SDL_log.h>

struct SDL_Rect;
struct SDL_Color;

class Util {
public:
    static void fatalError(const char *errMessage);
    static void fatalSDLError(const char *errMessage);
    static void log(const SDL_LogPriority &priority, const std::string &message);
	static void sleep(int ms);
    
    static SDL_Rect createRect(int x, int y, int w, int h);
    static SDL_Rect createRectCentered(int w, int h);
    static SDL_Rect createRectCenteredHorizontally(int y, int w, int h);
    static SDL_Rect createRectCenteredVertically(int x, int w, int h);
    static SDL_Color createColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

private:
    Util() {}
    ~Util() {}
};

#endif
