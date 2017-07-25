#include "../headers/BaseScreen.hpp"
#include <SDL2/SDL.h>
#include "../headers/Gahoodmon.hpp"
#include "../headers/Sprite.hpp"

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
            sprites[i]->update();
        }
    }
    onUpdate();
}

void BaseScreen::updateInBackground() { 
    for(unsigned int i = 0; i < sprites.size(); i++) {
        if(sprites[i] != NULL) {
            sprites[i]->updateInBackground();
        }
    }
    onUpdateInBackground();
}

void BaseScreen::handleInput(Gahoodmon *game, const SDL_Event &e) {
    //Gahoodmon handles quit event//
    onInput(game, e);
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

void BaseScreen::draw(SDL_Renderer *r) {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		if (sprites[i] != NULL) {
			sprites[i]->draw(r);
		}
	}
	onDraw(r);
}
