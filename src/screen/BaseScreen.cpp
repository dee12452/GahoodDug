#include "../headers/BaseScreen.hpp"
#include <SDL2/SDL.h>
#include "../headers/Gahoodmon.hpp"
#include "../headers/Sprite.hpp"

BaseScreen::BaseScreen() {}

BaseScreen::~BaseScreen() {
    for(unsigned int i = 0; i < sprites.size(); i++) {
        if(sprites[i] != NULL) {
            delete sprites[i];
            sprites[i] = NULL;
        }
    }
    sprites.clear();
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

std::vector<Sprite *> BaseScreen::getSprites() const {
    return sprites;
}
