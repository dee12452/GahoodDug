#ifndef GAHOOD_SPRITE_H
#define GAHOOD_SPRITE_H

#include <stdbool.h>
#include <stdint.h>

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_TouchFingerEvent;
typedef struct Sprite Sprite;

Sprite * gahood_spriteCreate(uint8_t);
void gahood_spriteLoadSpriteSheets(struct SDL_Renderer *);
void gahood_spriteDestroy(struct Sprite *);
void gahood_spriteDraw(struct SDL_Renderer *, struct Sprite *);
void gahood_spriteSetSrcDimensions(struct Sprite *, const struct SDL_Rect);
void gahood_spriteSetDstDimensions(struct Sprite *, const struct SDL_Rect);
void gahood_spriteClearDimensions(struct Sprite *);
struct SDL_Rect gahood_spriteGetSrcDimensions(struct Sprite *);
struct SDL_Rect gahood_spriteGetDstDimensions(struct Sprite *);

/* Logical Rendering Functions */
struct SDL_Rect gahood_spriteGetLogicalDstDimensions(struct Sprite *);
bool gahood_spriteCheckTouch(const struct SDL_TouchFingerEvent, struct Sprite *);
void gahood_spriteSetLogicalPosition(struct Sprite *, int, int);

#endif
