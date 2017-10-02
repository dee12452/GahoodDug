#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <SDL2/SDL_ttf.h>

struct SDL_Renderer;
class FontSprite;

#ifndef DEFAULT_FONT_SIZE
#define DEFAULT_FONT_SIZE 12
#endif

class Font {
public:
    Font(const char *fontFile);
    ~Font();

    FontSprite * createFontSprite(SDL_Renderer *renderer, const std::string &text, int pointSize) const;

private:
    std::string file;
};

#endif
