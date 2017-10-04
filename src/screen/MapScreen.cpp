#include "MapScreen.hpp"

#include "../world/World.hpp"

MapScreen::MapScreen(Game *game) : BaseScreen(game), world(new World(game)) {}

MapScreen::~MapScreen() {
    if(world != NULL) {
        delete world;
        world = NULL;
    }
}

void MapScreen::onDraw(Window *win) {
    world->draw(win);
}

void MapScreen::onUpdate(Game *game) {
    world->update(game);
}

void MapScreen::onUpdateInBackground(Game *) {}

void MapScreen::onInput(Game *, const SDL_Event &) {}

void MapScreen::onKeyInput(Game *, const uint8_t *) {}
