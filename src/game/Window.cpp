#include "../headers/Window.hpp"

#include <SDL2/SDL.h>
#include "../headers/ImageLoader.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Util.hpp"
#include "../headers/BaseScreen.hpp"
#include "../headers/Sprite.hpp"
#include "../headers/DisplayUtil.hpp"

Window::Window() {
    win = SDL_CreateWindow(Constants::GAME_TITLE, 
		DisplayUtil::getScreenWidth() / 2 - Constants::WINDOW_WIDTH / 2,
		DisplayUtil::getScreenHeight() / 2 - Constants::WINDOW_HEIGHT / 2, 
		Constants::WINDOW_WIDTH, 
		Constants::WINDOW_HEIGHT, Constants
		::WINDOW_FLAGS);
    if(win == NULL) {
        Util::fatalSDLError("Failed to initialize the window");
    }

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

    winTexture = SDL_CreateTexture(winRenderer,
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_TARGET, 
            Constants::WINDOW_WIDTH, 
            Constants::WINDOW_HEIGHT);
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
        if(ImageLoader::getInstance()->hasLoadedAllImages()) {
            loadImages = false;
        }
        else {
			ImageLoader::getInstance()->loadNextImage(winRenderer);
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
	if (screen != NULL) {
		screen->draw(this);
	}

    //Clear the window from previous rendering and show the new frame
    if(SDL_SetRenderTarget(winRenderer, NULL) < 0) {
        Util::fatalSDLError("Failed to set the render target to the window");
    }
    if(SDL_RenderClear(winRenderer) < 0) {
        Util::fatalSDLError("Failed to clear the window");
    }
    if(SDL_RenderCopy(winRenderer, winTexture, NULL, NULL) < 0) {
        Util::fatalSDLError("Failed to draw the texure to window");
    }
    SDL_RenderPresent(winRenderer);
}

void Window::setRenderTarget(SDL_Texture *t) const {
	if (SDL_SetRenderTarget(winRenderer, t) < 0) {
		Util::fatalSDLError("Failed to switch renderer to texture");
	}
}

void Window::resetRenderTarget() const {
	if (SDL_SetRenderTarget(winRenderer, winTexture) < 0) {
		Util::fatalSDLError("Failed to switch renderer to texture");
	}
}

void Window::drawTexture(SDL_Texture *t, SDL_Rect *s, SDL_Rect *d) const {
	if (SDL_RenderCopy(winRenderer, t, s, d) < 0) {
		Util::fatalSDLError("Failed to draw the texure to window");
	}
}

SDL_Texture * Window::createTransparentTexture(int w, int h) const { 
	SDL_Texture *t = SDL_CreateTexture(getWindowRenderer(),
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		w,
		h);
	setRenderTarget(t);
	if (SDL_SetRenderDrawBlendMode(winRenderer, SDL_BLENDMODE_BLEND) != 0) {
		Util::fatalSDLError("Failed to change render blend mode");
	}
	if (SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND) != 0) {
		Util::fatalSDLError("Failed to change texture blend mode");
	}
	if (SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, Constants::SPRITE_ALPHA_NONE) != 0) {
		Util::fatalSDLError("Failed to change texture blend mode");
	}
	if (SDL_RenderFillRect(winRenderer, NULL) != 0) {
		Util::fatalSDLError("Failed to fill transparent texture");
	}
	resetRenderTarget();
	if (SDL_SetRenderDrawBlendMode(winRenderer, SDL_BLENDMODE_NONE) != 0) {
		Util::fatalSDLError("Failed to change render blend mode");
	}
	if (SDL_SetRenderDrawColor(winRenderer, 0, 0, 0, Constants::SPRITE_ALPHA_FULL) != 0) {
		Util::fatalSDLError("Failed to reset render color");
	}
	return t;
}

SDL_Window * Window::getWindow() const { return win; }
SDL_Renderer * Window::getWindowRenderer() const { return winRenderer; }
SDL_Texture * Window::getWindowTexture() const { return winTexture; }
