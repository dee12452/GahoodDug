#include "WorldScreen.hpp"

#include <SDL2/SDL_events.h>
#include "../game/Game.hpp"
#include "../world/World.hpp"
#include "../world/WorldCharacter.hpp"
#include "../util/Constants.hpp"

WorldScreen::WorldScreen() : BaseScreen(), world(new World()) {}

WorldScreen::~WorldScreen() {
    if(world != NULL) {
        delete world;
        world = NULL;
    }
}

void WorldScreen::start(Game *game) { world->start(game); }

void WorldScreen::stop(Game *game) { world->stop(game); }

void WorldScreen::render(Window *win) { world->render(win); }

void WorldScreen::onInput(Game *, const SDL_Event &) {}

void WorldScreen::onKeyInput(Game *, const uint8_t *keys) {
	WorldCharacter *player = static_cast<WorldCharacter *> (world->getPlayer());
    bool movePlayer = false;

    if(keys[SDL_SCANCODE_LSHIFT]) {
        player->setMoveSpeed(Constants::CHARACTER_RUN_SPEED);
    }
    else {
        player->setMoveSpeed(Constants::CHARACTER_WALK_SPEED);
    }
    if(keys[SDL_SCANCODE_UP]) {
        player->move(FacingDirection::UP);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_DOWN]) {
        player->move(FacingDirection::DOWN);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        player->move(FacingDirection::RIGHT);
        movePlayer = true;
    }
    else if(keys[SDL_SCANCODE_LEFT]) {
        player->move(FacingDirection::LEFT);
        movePlayer = true;
    }

    if(!movePlayer) player->cancelNextMove();
}
