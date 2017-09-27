#include "BaseScreen.hpp"
#include <SDL2/SDL.h>
#include "../game/Gahoodmon.hpp"
#include "../game/Window.hpp"
#include "../game/Sprite.hpp"

BaseScreen::BaseScreen() {}

BaseScreen::~BaseScreen() {}

void BaseScreen::start() {
    onStart();
}

void BaseScreen::stop() {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		if (sprites[i] != NULL) {
			delete sprites[i];
			sprites[i] = NULL;
		}
	}
	sprites.clear();
    onStop();
}

void BaseScreen::update() {
    for(unsigned int i = 0; i < sprites.size(); i++) {
        if(sprites[i] != NULL) {
            //sprites[i]->update();
        }
    }
    onUpdate();
}

void BaseScreen::updateInBackground() { 
    for(unsigned int i = 0; i < sprites.size(); i++) {
        if(sprites[i] != NULL) {
            //sprites[i]->updateInBackground();
        }
    }
    onUpdateInBackground();
}

void BaseScreen::handleInput(Gahoodmon *game) {
    //Gahoodmon handles quit event//
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			game->quit();
		}
		else {
			onInput(game, e);
		}
	}
	const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
	handleKeyboard(keyboard);
}

void BaseScreen::addSprite(Sprite *sprite) {
    sprites.push_back(sprite);
}

void BaseScreen::removeSprite(Sprite *sprite) {
    for(unsigned int i = 0; i < sprites.size(); i++) {
        if(sprites[i] == sprite) {
            delete sprites[i];
            sprites[i] = NULL;
            std::swap(sprites[i], sprites[sprites.size() - 1]);
            sprites.pop_back();
            break;
        }
    }
}

std::vector<Sprite *> BaseScreen::getSprites() const {
    return sprites;
}

void BaseScreen::draw(Window *win) {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		if (sprites[i] != NULL) {
			sprites[i]->draw(win->getWindowRenderer());
		}
	}
	onDraw(win);
}
