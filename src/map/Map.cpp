#include "Map.hpp"
#include "Tileset.hpp"
#include "Tile.hpp"

#include <SDL2/SDL.h>
#include "../util/Constants.hpp"
#include "../game/Window.hpp"
#include "../util/Util.hpp"

Map::Map() {
	this->width = 0;
	this->height = 0;
	this->tileset = NULL;
}

Map::Map(int w, int h, std::vector<int **>tileCoords, Tileset *tileset) {
	this->width = w;
	this->height = h;
	this->tileset = tileset;
	this->mapTiles = tileCoords;
}

Map::~Map() {

	//Clear the map tiles
	for (unsigned int j = 0; j < mapTiles.size(); j++) {
		for (int i = 0; i < width / tileset->getTileWidth(); i++) {
			delete[] mapTiles[j][i];
			mapTiles[j][i] = NULL;
		}
		delete[] mapTiles[j];
		mapTiles[j] = NULL;
	}
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}

Tileset * Map::getTileset() const { return tileset; }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
int Map::getTileWidth() const { return getTileset()->getTile(0) == NULL ? 0 : getTileset()->getTileWidth(); } 
int Map::getTileHeight() const { return getTileset()->getTileHeight(); } 
std::vector<int **> Map::getLayers() const { return mapTiles; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::addLayer(int **tiles) { this->mapTiles.push_back(tiles); }
