#include "Window.hpp"

#include <SDL2/SDL.h>
#include "Game.hpp"
#include "../util/Constants.hpp"
#include "../util/Util.hpp"
#include "../util/DisplayUtil.hpp"
#include "../screen/BaseScreen.hpp"

Window::Window() {
    
    //Create the window
    win = SDL_CreateWindow(Constants::GAME_TITLE, 
		DisplayUtil::getScreenWidth() / 2 - Constants::WINDOW_WIDTH / 2,
		DisplayUtil::getScreenHeight() / 2 - Constants::WINDOW_HEIGHT / 2, 
		Constants::WINDOW_WIDTH, 
		Constants::WINDOW_HEIGHT, Constants
		::WINDOW_FLAGS);
    if(win == NULL) {
        Util::fatalSDLError("Failed to initialize the window");
    }

    //Create the renderer
    winRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if(winRenderer == NULL) {
        Util::fatalSDLError("Failed to initialize the window renderer");
    }
    //Make default render color black and set the window to black
	if (SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, Constants::SPRITE_ALPHA_FULL) != 0) {
		Util::fatalSDLError("Failed to set the renderer draw color");
	}
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to initially clear the renderer");
    }
    SDL_RenderPresent(winRenderer);
}

Window::~Window() {
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
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to clear the texture renderer");
    }

    //Draw the screen to the texture here
	if (screen != NULL) {
		screen->render(this);
	}

    SDL_RenderPresent(winRenderer);
}

void Window::setRenderTarget(SDL_Texture *targetTexture) const {
	if (SDL_SetRenderTarget(winRenderer, targetTexture) < 0) {
		Util::fatalSDLError("Failed to switch renderer to texture");
	}
}

void Window::resetRenderTarget() const {
	if (SDL_SetRenderTarget(winRenderer, NULL) < 0) {
		Util::fatalSDLError("Failed to switch renderer to texture");
	}
}

void Window::drawTexture(SDL_Texture *texture, SDL_Rect *srcRect, SDL_Rect *dstRect) const {
	if (SDL_RenderCopy(winRenderer, texture, srcRect, dstRect) < 0) {
		Util::fatalSDLError("Failed to draw the texure to window");
	}
}

void Window::clearRenderTarget() const {
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to clear the window");
    }
}

SDL_Texture * Window::createTransparentTexture(int width, int height) const { 
	SDL_Texture *texture = SDL_CreateTexture(getWindowRenderer(),
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width,
		height);
	if (texture == NULL) Util::fatalSDLError("Failed to create transparent texture");
	setRenderTarget(texture);
	if (SDL_SetRenderDrawBlendMode(winRenderer, SDL_BLENDMODE_BLEND) != 0) {
		Util::fatalSDLError("Failed to change render blend mode");
	}
	if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0) {
        Util::fatalSDLError("Failed to change texture blend mode");
	}
	if (SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, Constants::SPRITE_ALPHA_NONE) != 0) {
		Util::fatalSDLError("Failed to change render draw color");
	}
	if (SDL_RenderFillRect(winRenderer, NULL) != 0) {
		Util::fatalSDLError("Failed to fill transparent texture");
	}
	resetRenderTarget();
	if (SDL_SetRenderDrawBlendMode(winRenderer, SDL_BLENDMODE_NONE) != 0) {
		Util::fatalSDLError("Failed to change render blend mode back");
	}
	if (SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, Constants::SPRITE_ALPHA_FULL) != 0) {
		Util::fatalSDLError("Failed to reset render color");
	}
	return texture;
}

SDL_Texture * Window::createTexture(int width, int height) const {
	SDL_Texture *texture = SDL_CreateTexture(winRenderer,
		SDL_PIXELFORMAT_RGBA8888, 
		SDL_TEXTUREACCESS_TARGET, 
		width, 
		height);
	setRenderTarget(texture);
	clearRenderTarget();
	resetRenderTarget();
	return texture;
}

SDL_Window * Window::getWindow() const { return win; }
SDL_Renderer * Window::getWindowRenderer() const { return winRenderer; }
