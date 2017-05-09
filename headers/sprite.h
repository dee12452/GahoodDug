#ifndef GAHOOD_SPRITE_H
#define GAHOOD_SPRITE_H

struct SDL_Renderer;
struct SDL_Rect;
typedef struct Sprite Sprite;

struct Sprite * gahood_spriteCreate(struct SDL_Renderer *, const char *, const struct SDL_Rect, const struct SDL_Rect);
void gahood_spriteDestroy(struct Sprite *);
void gahood_spriteDraw(struct SDL_Renderer *, struct Sprite *);
void gahood_spriteSetSrcDimensions(struct Sprite *, const struct SDL_Rect);
void gahood_spriteSetDstDimensions(struct Sprite *, const struct SDL_Rect);
struct SDL_Rect gahood_spriteGetSrcDimensions(struct Sprite *);
struct SDL_Rect gahood_spriteGetDstDimensions(struct Sprite *);

#endif
