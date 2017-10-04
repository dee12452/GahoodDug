#include "Font.hpp"
#include "FontSprite.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../util/Util.hpp"
#include "../util/Constants.hpp"

struct SDL_Surface;

Font::Font(const char *fontFile) : file(fontFile) {}

Font::~Font() {}

FontSprite * Font::createFontSprite(SDL_Renderer *renderer, const std::string &text, int pointSize) const {
    TTF_Font *font = TTF_OpenFont(file.c_str(), pointSize);
    if(font == NULL) {
        std::string message("Failed to open font: " + file);
        Util::fatalSDLError(message.c_str());
    }
    SDL_Color color;
    color.r = 0; color.b = 0; color.g = 0;
    color.a = Constants::SPRITE_ALPHA_FULL;
    return new FontSprite(renderer, font, text, color);
}

FontSprite * Font::createFontSprite(SDL_Renderer *renderer, const std::string &text) const  {
    return createFontSprite(renderer, text, DEFAULT_FONT_SIZE);
}
