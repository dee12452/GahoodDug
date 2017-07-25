#include "../headers/Map.hpp"

#include <SDL2/SDL_rect.h>
#include "../headers/Constants.hpp"
#include "../headers/Tileset.hpp"
#include "../headers/Tile.hpp"

Map::Map() {
	this->width = 0;
	this->height = 0;
	this->tileset = NULL;
}

Map::Map(int w, int h, int **tileCoords, Tileset *tileset) {
	this->width = w;
	this->height = h;
	this->tileset = tileset;
	this->mapTiles = tileCoords;
}

Map::~Map() {
	for (int i = 0; i < width / Constants::TILE_WIDTH; i++) {
		delete[] mapTiles[i];
		mapTiles[i] = NULL;
	}
	delete[] mapTiles;
	mapTiles = NULL;
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}

void Map::draw(SDL_Renderer *r) {
	for (int i = 0; i < width / Constants::TILE_WIDTH; i++) {
		for (int j = 0; j < height / Constants::TILE_HEIGHT; j++) {
			Tile *tile = tileset->getTile(mapTiles[i][j]);
			if (tile != NULL) {
				SDL_Rect dstRect;
				dstRect.x = i * Constants::TILE_WIDTH; dstRect.h = j * Constants::TILE_HEIGHT;
				dstRect.w = Constants::TILE_WIDTH; dstRect.h = Constants::TILE_HEIGHT;
				tile->setDestinationRect(dstRect);
				tile->draw(r);
			}
		}
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
}

Tileset * Map::getTileset() const { return tileset; }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::setTiles(int **tiles) { this->mapTiles = tiles; }

