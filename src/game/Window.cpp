#include "../headers/Window.hpp"

#include <SDL2/SDL.h>
#include "../headers/ImageUtil.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Util.hpp"
#include "../headers/BaseScreen.hpp"
#include "../headers/Sprite.hpp"

Window::Window() {
    win = SDL_CreateWindow(Constants::GAME_TITLE, 0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, Constants::WINDOW_FLAGS);
    if(win == NULL) {
        Util::fatalSDLError("Failed to initialize the window");
    }

    winRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(winRenderer == NULL) {
        Util::fatalSDLError("Failed to initialize the window renderer");
    }
    //Make default render color black and set the window to black
    SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, 0);
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to initially clear the renderer");
    }
    SDL_RenderPresent(winRenderer);

    winTexture = SDL_CreateTexture(winRenderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);
    if(winTexture == NULL) {
        Util::fatalSDLError("Failed to initialize the window texture");
    }

    loadImages = true;
}

Window::~Window() {
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

void Window::render(BaseScreen *screen) {
    //Check to see if any images need loading
    if(loadImages) {
        if(ImageUtil::getInstance()->hasLoadedAllImages()) {
            loadImages = false;
        }
        else {
            ImageUtil::getInstance()->loadNextImage(winRenderer);
        }
    }
    
    //Clear the texture from previous rendering
    if(SDL_SetRenderTarget(winRenderer, winTexture) < 0) {
        Util::fatalSDLError("Failed to switch renderer to texture");
    }
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to clear the texture renderer");
    }

    //Draw the screen to the texture here
    screen->drawScreen(winRenderer);

    //Clear the window from previous rendering and show the new frame
    if(SDL_SetRenderTarget(winRenderer, NULL) < 0) {
        Util::fatalSDLError("Failed to set the render target to the window");
    }
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to ");
    }
    if(SDL_RenderCopy(winRenderer, winTexture, NULL, NULL) < 0) {
        Util::fatalSDLError("Failed to ");
    }
    SDL_RenderPresent(winRenderer);
}
