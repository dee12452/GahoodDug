#include "WorldScreen.hpp"

#include <SDL2/SDL_events.h>
#include "../game/Game.hpp"
#include "../world/World.hpp"
#include "../world/WorldCharacter.hpp"
#include "../util/Constants.hpp"

WorldScreen::WorldScreen() : BaseScreen(), world(NULL) {}

WorldScreen::~WorldScreen() {
    if(world != NULL) {
        delete world;
        world = NULL;
    }
}

void WorldScreen::start(Game *game) {
	world = new World(game);
	game->schedule(world->getPlayer());
}

void WorldScreen::stop(Game *game) {
	game->unschedule(world->getPlayer());
}

void WorldScreen::render(Window *win) {
    world->render(win);
}

void WorldScreen::onInput(Game *, const SDL_Event &) {
}

void WorldScreen::onKeyInput(Game *, const uint8_t *keys) {
    bool movePlayer = false;

    if(keys[SDL_SCANCODE_LSHIFT]) {
        world->getPlayer()->setMoveSpeed(Constants::CHARACTER_RUN_SPEED);
    }
    else {
        world->getPlayer()->setMoveSpeed(Constants::CHARACTER_WALK_SPEED);
    }
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
