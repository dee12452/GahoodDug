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
	this->playerCharacter = NULL;
}

Map::Map(int w, int h, std::vector<int **>tileCoords, Tileset *tileset) {
	this->width = w;
	this->height = h;
	this->tileset = tileset;
	this->mapTiles = tileCoords;
	this->playerCharacter = NULL;
}

Map::~Map() {
	//Clear the map tiles
	for (unsigned int j = 0; j < mapTiles.size(); j++) {
		for (int i = 0; i < width / Constants::TILE_WIDTH; i++) {
			delete[] mapTiles[j][i];
			mapTiles[j][i] = NULL;
		}
		delete[] mapTiles[j];
		mapTiles[j] = NULL;
	}
	mapLayers.clear();

	//Clear the map layers (textures)
	for (unsigned int j = 0; j < mapLayers.size(); j++) {
		SDL_DestroyTexture(mapLayers[j]);
		mapLayers[j] = NULL;
	}
	mapLayers.clear();

	//Delete the overworld character
	if (playerCharacter != NULL) {
		delete playerCharacter;
		playerCharacter = NULL;
	}
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}

void Map::draw(Window *win) {
	//The map has not been generated yet
	if (mapLayers.size() < 1) {
		generate(win);
	}

	//draw the map in respect to the player
	else if(playerCharacter != NULL) {
		SDL_Texture *map = win->createTransparentTexture(width * Constants::TILE_WIDTH, 
			height * Constants::TILE_HEIGHT);
		win->setRenderTarget(map);
		for (unsigned int i = 0; i < mapLayers.size(); i++) {
			win->drawTexture(mapLayers[i], NULL, NULL);
			if (i == playerCharacter->getCurrentMapLayer()) {
				playerCharacter->draw(win);
			}
		}
		SDL_Rect mapSrc;
		mapSrc.x = (playerCharacter->getX() + playerCharacter->getWidth() / 2) - ((Constants::MAP_NUM_TILES_WIDTH / 2) * Constants::TILE_WIDTH);
		mapSrc.y = (playerCharacter->getY() + playerCharacter->getHeight() / 2) - ((Constants::MAP_NUM_TILES_HEIGHT / 2) * Constants::TILE_HEIGHT);
		mapSrc.w = Constants::TILE_WIDTH * Constants::MAP_NUM_TILES_WIDTH;
		mapSrc.h = Constants::TILE_HEIGHT * Constants::MAP_NUM_TILES_HEIGHT;
		win->resetRenderTarget();
		win->drawTexture(map, &mapSrc, NULL);
		SDL_DestroyTexture(map);
		map = NULL;
	}

	//since there is no player,
	//draw the map in its entirety
	else {
		SDL_Texture *map = win->createTransparentTexture(width * Constants::TILE_WIDTH,
			height * Constants::TILE_HEIGHT);
		win->setRenderTarget(map);
		for (unsigned int i = 0; i < mapLayers.size(); i++) {
			win->drawTexture(mapLayers[i], NULL, NULL);
		}
		win->resetRenderTarget();
		win->drawTexture(map, NULL, NULL);
		SDL_DestroyTexture(map);
		map = NULL;
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
	//If there is already a map or the tileset image hasn't loaded, don't generate the map
	if (mapLayers.size() > 0 || ImageLoader::getInstance()->getImage(tileset->getImage()) == NULL) return;
	
	for (unsigned int layer = 0; layer < mapTiles.size(); layer++) {
		SDL_Texture *layerTexture = win->createTransparentTexture(
			Constants::TILE_WIDTH * width,
			Constants::TILE_HEIGHT * height
		);
		win->setRenderTarget(layerTexture);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (mapTiles[layer][j][i] - 1 < 0) continue;
				Tile *currTile = tileset->getTile(mapTiles[layer][j][i] - 1);
				SDL_Rect dst;
				dst.x = j * Constants::TILE_WIDTH;
				dst.y = i * Constants::TILE_HEIGHT;
				dst.w = Constants::TILE_WIDTH;
				dst.h = Constants::TILE_HEIGHT;
				currTile->setDestinationRect(dst);
				currTile->draw(win);
			}
		}
		mapLayers.push_back(layerTexture);
	}
	win->resetRenderTarget();
}

void Map::placePlayer(int x, int y) {
	if (playerCharacter == NULL) {
		playerCharacter = new PlayerCharacter(Constants::IMAGE_CHARACTER_1);
	}
	playerCharacter->setX(x);
	playerCharacter->setY(y);
}

void Map::removePlayer() {
	if (playerCharacter != NULL) {
		delete playerCharacter;
		playerCharacter = NULL;
	}
}

Tileset * Map::getTileset() const { return tileset; }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
std::vector<int **> Map::getLayers() const { return mapTiles; }
BaseCharacter * Map::getPlayer() const { return playerCharacter; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::addLayer(int **tiles) { this->mapTiles.push_back(tiles); }

