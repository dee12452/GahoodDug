#include "../headers/Map.hpp"

#include <SDL2/SDL.h>
#include "../headers/Constants.hpp"
#include "../headers/Tileset.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Window.hpp"
#include "../headers/Util.hpp"
#include "../headers/ImageLoader.hpp"
#include "../headers/PlayerCharacter.hpp"

Map::Map() {
	this->width = 0;
	this->height = 0;
	this->tileset = NULL;
	this->mapTexture = NULL;
	this->playerCharacter = new PlayerCharacter(Constants::IMAGE_CHARACTER_1, 0, 0, 32, 48, 0, 0, 32, 48);
}

Map::Map(int w, int h, std::vector<int **>tileCoords, Tileset *tileset) {
	this->width = w;
	this->height = h;
	this->tileset = tileset;
	this->mapLayers = tileCoords;
	this->mapTexture = NULL;
	this->playerCharacter = new PlayerCharacter(Constants::IMAGE_CHARACTER_1, 0, 0, 32, 48, 0, 0, 32, 48);
}

Map::~Map() {
	for (unsigned int j = 0; j < mapLayers.size(); j++) {
		for (int i = 0; i < width / Constants::TILE_WIDTH; i++) {
			delete[] mapLayers[j][i];
			mapLayers[j][i] = NULL;
		}
		delete[] mapLayers[j];
		mapLayers[j] = NULL;
	}
	mapLayers.clear();

	if (mapTexture != NULL) {
		SDL_DestroyTexture(mapTexture);
		mapTexture = NULL;
	}
	if (playerCharacter != NULL) {
		delete playerCharacter;
		playerCharacter = NULL;
	}
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}

void Map::draw(Window *win) {
	if (mapTexture == NULL) {
		generate(win);
	}
	else {
		SDL_RenderCopy(win->getWindowRenderer(), mapTexture, NULL, NULL);
		playerCharacter->draw(win);
	}
}

void Map::update() {
	int i = 0;
	Tile *tile = tileset->getTile(i);
	while (tile != NULL) {
		tile->update();
		i++;
		tile = tileset->getTile(i);
	}
	if (playerCharacter != NULL) {
		playerCharacter->update();
	}
}

void Map::generate(Window *win) {
	if (mapTexture == NULL && ImageLoader::getInstance()->getImage(tileset->getImage()) != NULL) {
		mapTexture = SDL_CreateTexture(win->getWindowRenderer(), 
			SDL_PIXELFORMAT_RGBA8888, 
			SDL_TEXTUREACCESS_TARGET, 
			width * Constants::TILE_WIDTH, 
			height * Constants::TILE_HEIGHT);
		if (mapTexture == NULL) {
			Util::fatalSDLError("Failed to initialize the map texture");
		}
		if (SDL_SetRenderTarget(win->getWindowRenderer(), mapTexture) != 0) {
			Util::fatalSDLError("Failed to switch renderer to texture");
		}
		if (SDL_RenderClear(win->getWindowRenderer()) < 0) {
			Util::fatalSDLError("Failed to clear the texture renderer");
		}
		for (unsigned int layer = 0; layer < mapLayers.size(); layer++) {
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (mapLayers[layer][j][i] - 1 < 0) continue;
					Tile *currTile = tileset->getTile(mapLayers[layer][j][i] - 1);
					SDL_Rect dst;
					dst.x = j * Constants::TILE_WIDTH;
					dst.y = i * Constants::TILE_HEIGHT;
					dst.w = Constants::TILE_WIDTH;
					dst.h = Constants::TILE_HEIGHT;
					currTile->setDestinationRect(dst);
					currTile->draw(win);
				}
			}
		}
		if (SDL_SetRenderTarget(win->getWindowRenderer(), win->getWindowTexture()) != 0) {
			Util::fatalSDLError("Failed to switch renderer to texture");
		}
	}
}

Tileset * Map::getTileset() const { return tileset; }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
std::vector<int **> Map::getLayers() const { return mapLayers; }
BaseCharacter * Map::getPlayer() const { return playerCharacter; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::addLayer(int **tiles) { this->mapLayers.push_back(tiles); }

