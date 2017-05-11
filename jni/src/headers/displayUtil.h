#ifndef GAHOOD_DISPLAY_UTIL
#define GAHOOD_DISPLAY_UTIL

#include <stdbool.h>

struct SDL_Window;
struct SDL_Rect;
struct Sprite;

int gahood_displayGetScreenWidth();
int gahood_displayGetScreenHeight();
void gahood_displayOnScreenChange();
void gahood_displaySetWindowDimensions(struct SDL_Window *, int, int);
struct SDL_Rect gahood_displayGetSpriteLogicalPosition(struct Sprite *);
bool gahood_displayCheckCollision(int, int, struct Sprite *);

#endif
