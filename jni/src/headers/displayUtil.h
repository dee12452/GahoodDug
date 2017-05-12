#ifndef GAHOOD_DISPLAY_UTIL
#define GAHOOD_DISPLAY_UTIL

#include <stdbool.h>

struct SDL_Window;
struct SDL_TouchFingerEvent;
struct SDL_Rect;
struct Sprite;

int gahood_displayGetScreenWidth();
int gahood_displayGetScreenHeight();
int gahood_displayGetRenderWidth();
int gahood_displayGetRenderHeight();
struct SDL_Rect gahood_displayGetSpriteLocation(struct Sprite *);
void gahood_displaySetWindowDimensions(struct SDL_Window *, int, int);
bool gahood_displayCheckCollision(int, int, struct Sprite *);

#endif
