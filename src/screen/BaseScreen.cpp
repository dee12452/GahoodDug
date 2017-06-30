#include "../headers/BaseScreen.hpp"
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

std::vector<Sprite *> BaseScreen::getSprites() const {
    return sprites;
}
