#ifndef FONT_HPP
#define FONT_HPP

#include <string>
#include <SDL2/SDL_ttf.h>

class Window;
class FontSprite;

#ifndef DEFAULT_FONT_SIZE
#define DEFAULT_FONT_SIZE 20
#endif

class Font {
public:
    Font(const char *fontFile);
    ~Font();

    FontSprite * createFontSprite(Window *win, const std::string &text, int pointSize) const;
    FontSprite * createFontSprite(Window *win, const std::string &text) const;

private:
    std::string file;
};

#endif
