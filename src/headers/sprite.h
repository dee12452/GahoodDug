#ifndef GAHOOD_SPRITE_H
#define GAHOOD_SPRITE_H

struct SDL_Texture; 
struct SDL_Rect;
struct SDL_Renderer;
struct Sprite;

struct Sprite * gahood_createSprite(struct SDL_Renderer *, const char *);
void gahood_destroySprite(struct Sprite *);

#endif
