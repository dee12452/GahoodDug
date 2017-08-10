#include "../headers/MapScreen.hpp"

#include "../headers/Gahoodmon.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Image.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/MapLoader.hpp"
#include "../headers/Map.hpp"
#include "../headers/BaseCharacter.hpp"
#include "../headers/Util.hpp"
#include <SDL2/SDL.h>

MapScreen::MapScreen() {
	test = NULL;
}

MapScreen::~MapScreen() {}

void MapScreen::onDraw(Window *win) {
	test->draw(win);
}

void MapScreen::onStart() {
	test = MapLoader::getInstance()->loadMap(Constants::MAP_FILE_TEST);
	test->placePlayer(288, 288);
}

void MapScreen::onStop() {
	if (test != NULL) {
		delete test;
		test = NULL;
	}
}

void MapScreen::onUpdate() {
	if (test != NULL) {
		test->update();
	}
}

void MapScreen::onUpdateInBackground() {
}

void MapScreen::onInput(Gahoodmon *game, const SDL_Event &e) {
}

void MapScreen::handleKeyboard(const uint8_t *keyScanCodes) {
	if (test != NULL && test->getPlayer() != NULL) {
		if (keyScanCodes[SDL_SCANCODE_DOWN]) {
			test->getPlayer()->move(CH_DOWN);
		}
		else if (keyScanCodes[SDL_SCANCODE_UP]) {
			test->getPlayer()->move(CH_UP);
		}
		else if (keyScanCodes[SDL_SCANCODE_LEFT]) {
			test->getPlayer()->move(CH_LEFT);
		}
		else if (keyScanCodes[SDL_SCANCODE_RIGHT]) {
			test->getPlayer()->move(CH_RIGHT);
		}
		else {
			test->getPlayer()->cancelNextMove();
		}
	}
}
