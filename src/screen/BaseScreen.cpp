#include "BaseScreen.hpp"
#include <SDL2/SDL.h>

BaseScreen::BaseScreen(Game *) {}

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
