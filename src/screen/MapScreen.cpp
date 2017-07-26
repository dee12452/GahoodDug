#include "../headers/MapScreen.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Constants.hpp"
#include "../headers/Image.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/MapLoader.hpp"
#include "../headers/Map.hpp"
#include <SDL2/SDL_log.h>

MapScreen::MapScreen() {}

MapScreen::~MapScreen() {}

void MapScreen::onDraw(SDL_Renderer *) {
}

void MapScreen::onStart() {
	addSprite(new Image(Constants::IMAGE_ID_TEST,
		0, 0, 32, 32,
		0, 0, 500, 500));
	Map *temp = MapLoader::getInstance()->loadMap(Constants::MAP_FILE_TEST);
	delete temp;
	temp = NULL;
}

void MapScreen::onStop() {}

void MapScreen::onUpdate() {
}

void MapScreen::onUpdateInBackground() {
}

void MapScreen::onInput(Gahoodmon *, const SDL_Event &) {}
