#include "../headers/MapScreen.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Constants.hpp"

MapScreen::MapScreen() {}

MapScreen::~MapScreen() {}

void MapScreen::drawScreen(SDL_Renderer *r) {
    getSprites()[0]->draw(r);
}

void MapScreen::onStart() {
    std::vector<std::pair<int, int>> coords;
    coords.push_back(std::pair<int, int> (0, 0));
    coords.push_back(std::pair<int, int> (32, 0));
    coords.push_back(std::pair<int, int> (64, 0));
    coords.push_back(std::pair<int, int> (96, 0));
    Tile *tile = new Tile(Constants::IMAGE_ID_TEST, coords, 500);
    tile->setDestinationRect(0, 0, 32, 32);
    addSprite(tile);
    tile = NULL;
}

void MapScreen::onStop() {}

void MapScreen::onUpdate() {
    getSprites()[0]->update();
}

void MapScreen::onUpdateInBackground() {
}

void MapScreen::onInput(Gahoodmon *, const SDL_Event &) {}
