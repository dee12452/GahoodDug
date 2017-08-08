#include "../headers/MapScreen.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Image.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/MapLoader.hpp"
#include "../headers/Map.hpp"
#include <SDL2/SDL_log.h>

MapScreen::MapScreen() {
	test = NULL;
}

MapScreen::~MapScreen() {}

void MapScreen::onDraw(Window *win) {
	test->draw(win);
}

void MapScreen::onStart() {
	test = MapLoader::getInstance()->loadMap(Constants::MAP_FILE_TEST);
}

void MapScreen::onStop() {
	if (test != NULL) {
		delete test;
		test = NULL;
	}
}

void MapScreen::onUpdate() {
}

void MapScreen::onUpdateInBackground() {
}

void MapScreen::onInput(Gahoodmon *, const SDL_Event &) {}
