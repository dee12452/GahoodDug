#include "MapScreen.hpp"

#include "../world/World.hpp"
#include "../world/Character.hpp"
#include <SDL2/SDL_events.h>

MapScreen::MapScreen(Game *game) : BaseScreen(game), world(new World(game)) {}

MapScreen::~MapScreen() {
    if(world != NULL) {
        delete world;
        world = NULL;
    }
}

void MapScreen::drawScreen(Window *win) const {
    world->drawWorld(win);
}

void MapScreen::onInput(Game *, const SDL_Event &) {
}

void MapScreen::onKeyInput(Game *, const uint8_t *keys) {
    bool movePlayer = false;

    if(keys[SDL_SCANCODE_UP]) {
        world->getPlayer()->move(FacingDirection::UP);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_DOWN]) {
        world->getPlayer()->move(FacingDirection::DOWN);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        world->getPlayer()->move(FacingDirection::RIGHT);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_LEFT]) {
        world->getPlayer()->move(FacingDirection::LEFT);
        movePlayer = true;
    }

    if(!movePlayer) world->getPlayer()->cancelNextMove();
}
