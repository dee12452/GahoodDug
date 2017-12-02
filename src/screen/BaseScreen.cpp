#include "BaseScreen.hpp"
#include <SDL2/SDL.h>

BaseScreen::BaseScreen() {}

BaseScreen::~BaseScreen() {}

void BaseScreen::handleInput(Game *game) {
    //Game handles quit event//
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
	onKeyInput(game, keyboard);
}

void BaseScreen::start(Game *game) {}
void BaseScreen::pause(Game *game) {}
void BaseScreen::resume(Game *game) {}
void BaseScreen::stop(Game *game) {}

