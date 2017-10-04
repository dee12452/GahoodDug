#include "SpriteSheet.hpp"

#include "Sprite.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "../util/Util.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer *renderer, const char *pathToImage) {
    sheet = IMG_LoadTexture(renderer, pathToImage);
    if(sheet == NULL) {
        std::string message = "Failed to load image: ";
        Util::fatalSDLError((message + pathToImage).c_str());
    }
}

SpriteSheet::~SpriteSheet() {
    SDL_DestroyTexture(sheet);
    sheet = NULL;
}

Sprite * SpriteSheet::createSprite() const {
    return new Sprite(sheet);
}

Sprite * SpriteSheet::createSprite(int srcX, int srcY, int srcW, int srcH,
        int dstX, int dstY, int dstW, int dstH) const {
    return new Sprite(sheet, srcX, srcY, srcW, srcH, dstX, dstY, dstW, dstH);
}

Sprite * SpriteSheet::createSprite(const SDL_Rect &srcRect, const SDL_Rect &dstRect) const {
    return new Sprite(sheet, srcRect, dstRect);
}
