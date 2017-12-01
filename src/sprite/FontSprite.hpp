#ifndef FONT_SPRITE_HPP
#define FONT_SPRITE_HPP

#include <string>
#include <SDL2/SDL_ttf.h>

class Sprite;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Color;

class FontSprite {
public:
    FontSprite(SDL_Renderer *renderer, TTF_Font *targetFont, const std::string &newText, const SDL_Color &color);
    ~FontSprite();

    void setText(SDL_Renderer *renderer, const std::string &newText);
    void setColor(SDL_Renderer *renderer, const SDL_Color &color);
    void draw(SDL_Renderer *renderer);

    std::string getText() const;
    SDL_Color getColor() const;
    Sprite * getSprite() const;

private:
    void createNewFontTexture(SDL_Renderer *renderer);

    std::string text;
    TTF_Font *font;
    SDL_Color *textColor;
    Sprite *sprite;
    SDL_Texture *texture;
};

#endif
