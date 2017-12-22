#ifndef FONT_SPRITE_HPP
#define FONT_SPRITE_HPP

#include <string>
#include <SDL2/SDL_ttf.h>

class Sprite;
class Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Color;

class FontSprite {
public:
    FontSprite(Window *win, TTF_Font *targetFont, const std::string &newText, const SDL_Color &color);
    ~FontSprite();

    void setText(Window *win, const std::string &newText);
    void setColor(Window *win, const SDL_Color &color);
    void draw(Window *win) const;

    std::string getText() const;
    SDL_Color getColor() const;
    Sprite * getSprite() const;

private:
    void createNewFontTexture(Window *win);

    std::string text;
    TTF_Font *font;
    SDL_Color *textColor;
    Sprite *sprite;
    SDL_Texture *texture;
};

#endif
