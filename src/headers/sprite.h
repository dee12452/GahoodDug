#ifndef GAHOOD_SPRITE_H
#define GAHOOD_SPRITE_H

struct SDL_Texture; 
struct SDL_Rect;
struct SDL_Renderer;
typedef struct Sprite Sprite;

struct Sprite * gahood_spriteCreate(struct SDL_Renderer *, const char *);
struct Sprite * gahood_spriteCreateWithDimensions(struct SDL_Renderer *, const char *, struct SDL_Rect, struct SDL_Rect);
void gahood_spriteDestroy(struct Sprite *);
void gahood_spriteDraw(struct SDL_Renderer *, Sprite *);
struct SDL_Rect gahood_spriteGetSourceRect(Sprite *);
void gahood_spriteSetSourceRect(Sprite *, int, int, int, int);
struct SDL_Rect gahood_spriteGetDestinationRect(Sprite *);
void gahood_spriteSetDestinationRect(Sprite *, int, int, int, int);

#endif
