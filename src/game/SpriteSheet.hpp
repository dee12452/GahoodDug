#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <string>

class Sprite;
struct SDL_Texture;
struct SDL_Rect;
struct SDL_Renderer;

class SpriteSheet {
public:

    /* Create a sprite sheet from a path to an image */
    SpriteSheet(SDL_Renderer *renderer, const char *pathToImage);
    ~SpriteSheet();

    /* Create Sprites from the SpriteSheet 
     * This should be the main way Sprites are created */
    Sprite * createSprite() const;
    Sprite * createSprite(int srcX, int srcY, int srcW, int srcH, 
            int dstX, int dstY, int dstW, int dstH) const;
    Sprite * createSprite(const SDL_Rect &srcRect, const SDL_Rect &dstRect) const;

private:
    SDL_Texture *sheet;
    std::string sheetName;
};

#endif
