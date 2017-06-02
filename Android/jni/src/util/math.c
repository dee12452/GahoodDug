#include <math.h>
#include <stdlib.h>
#include <SDL.h>
#include "../headers/math.h"
#include "../headers/displayUtil.h"

int
gahood_mathMax(int i1, int i2) {
    if(i1 > i2) {
        return i1;
    }
    return i2;
}

int
gahood_mathMin(int i1, int i2) {
    if(i1 < i2) {
        return i1;
    }
    return i2;
}

double
gahood_mathGetDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double
gahood_mathGetTriangleHypotenuse(int w, int h) {
    return sqrt(pow(w, 2) + pow(h, 2));
}

void
gahood_mathGetControllerTouchPosition(float eX, float eY, int *touchX, int *touchY, const SDL_Rect circle) {
    int circleCenterX = circle.x + circle.w / 2;
    int circleCenterY = circle.y + circle.h / 2;
    int x = eX * gahood_displayGetScreenWidth();
    int y = eY * gahood_displayGetScreenHeight();
    double dist = gahood_mathGetDistance(circleCenterX, circleCenterY, x, y); 
    if(dist > circle.w / 2) {
        *touchX = circleCenterX + (circle.w / 2) * ((x - circleCenterX) / dist);
        *touchY = circleCenterY + (circle.h / 2) * ((y - circleCenterY) / dist);
    }
    else {
        *touchX = eX * gahood_displayGetScreenWidth();
        *touchY = eY * gahood_displayGetScreenHeight();
    }
}
