#ifndef GAHOOD_MATH_H
#define GAHOOD_MATH_H

struct SDL_Rect;

int gahood_mathMax(int, int);
int gahood_mathMin(int, int);
void gahood_mathGetControllerTouchPosition(float, float, int *, int *, const struct SDL_Rect);
double gahood_mathGetDistance(int, int, int, int);
double gahood_mathGetTriangleHypotenuse(int, int);

#endif 
