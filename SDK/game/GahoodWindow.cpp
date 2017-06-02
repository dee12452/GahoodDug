#include "../headers/GahoodWindow.hpp"

#include <SDL2/SDL.h>
#include "../headers/GahoodTimer.hpp"

GahoodWindow::GahoodWindow(const char *title, int width, int height, uint32_t flags, int fps) {
    
    //Create the fps timer
    unsigned int fpsMs = 1000 / fps;
    fpsTimer = new GahoodTimer(fpsMs);

    //Create the window
    win = SDL_CreateWindow(title,
            0, 
            0,
            width, 
            height,
            flags);
    if(win == NULL) {
        //Error
    }

    //Create the renderer
    winRenderer = SDL_CreateRenderer(win, 
            -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(winRenderer == NULL) {
        //Error
    }

    //Create the texture
    winTexture = SDL_CreateTexture(winRenderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            width,
            height);
    if(winTexture == NULL) {
        //Error
    }
}

GahoodWindow::~GahoodWindow() {
    if(fpsTimer != NULL) {
        delete fpsTimer;
        fpsTimer = NULL;
    }
    if(winTexture != NULL) {
        SDL_DestroyTexture(winTexture);
        winTexture = NULL;
    }
    if(winRenderer != NULL) {
        SDL_DestroyRenderer(winRenderer);
        winRenderer = NULL;
    }
    if(win != NULL) {
        SDL_DestroyWindow(win);
        win = NULL;
    }
}
