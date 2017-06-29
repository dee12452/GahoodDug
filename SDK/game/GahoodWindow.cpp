#include "../headers/GahoodWindow.hpp"

#include <SDL2/SDL.h>
#include "../headers/GahoodTimer.hpp"
#include "../headers/GahoodUtil.hpp"

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
        GahoodUtil::fatalSDLError("Failed to create the window");
    }

    //Create the renderer
    winRenderer = SDL_CreateRenderer(win, 
            -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(winRenderer == NULL) {
        //Error
        GahoodUtil::fatalSDLError("Failed to create the window renderer");
    }
    //Set draw color to black
    if(SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, 255) < 0) {
        GahoodUtil::fatalSDLError("Failed to set renderer color");
    }

    //Create the texture
    winTexture = SDL_CreateTexture(winRenderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            width,
            height);
    if(winTexture == NULL) {
        //Error
        GahoodUtil::fatalSDLError("Failed to create the window texture");
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

bool GahoodWindow::shouldRender() const {
    return fpsTimer->check();
}

void GahoodWindow::initRender() const {
    if(SDL_RenderClear(winRenderer) < 0) {
        GahoodUtil::fatalSDLError("Failed to clear the renderer");
    }

    if(SDL_SetRenderTarget(winRenderer, winTexture) < 0) {
        GahoodUtil::fatalSDLError("Failed to change the render target");
    }

    if(SDL_RenderClear(winRenderer) < 0) {
        GahoodUtil::fatalSDLError("Failed to clear the renderer");
    }
}

void GahoodWindow::draw() const {
    /* Draw desired stuff here */

    if(SDL_SetRenderTarget(winRenderer, NULL) < 0) {
        GahoodUtil::fatalSDLError("Failed to change the render target");
    }

    if(SDL_RenderCopy(winRenderer, winTexture, NULL, NULL) < 0) {
        GahoodUtil::fatalSDLError("Failed to draw texture to screen");
    } 

    SDL_RenderPresent(winRenderer);
}

SDL_Window * GahoodWindow::getWindow() const {
    return win;
}

SDL_Renderer * GahoodWindow::getRenderer() const {
    return winRenderer;
}

SDL_Texture * GahoodWindow::getTexture() const {
    return winTexture;
}

void GahoodWindow::setFramesPerSecond(int fps) const {
    if(fpsTimer != NULL) {
        unsigned int fpsMs = 1000 / fps;
        fpsTimer->setTargetMs(fpsMs);
    }
}
