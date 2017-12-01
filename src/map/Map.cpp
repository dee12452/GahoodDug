#include "Map.hpp"
#include "Tileset.hpp"
#include "Tile.hpp"

#include <SDL2/SDL.h>
#include "../util/Constants.hpp"
#include "../game/Window.hpp"
#include "../game/Game.hpp"
#include "../util/Util.hpp"
#include "../game/Sprites.hpp"

Map::Map() :
	width(0), height(0), tileset(NULL), generated(false) {
}

Map::Map(int w, int h, std::vector<int **>tileCoords, Tileset *tileset) :
	width(w), height(h), mapTiles(tileCoords), tileset(tileset), generated(false) {
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

	//Delete the map textures
	for (unsigned int i = 0; i < mapTextures.size(); i++) {
		SDL_DestroyTexture(mapTextures[i]);
		mapTextures[i] = NULL;
	}
	mapTextures.clear();
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}

void Map::generate(Game *game) {
	if (width == 0 || height == 0 || generated || tileset == NULL) return;

	Sprite *tilesetSprite = game->getSpriteSheet(tileset->getImagePath())->createSprite();
	Window *win = game->getWindow();

	for (unsigned int layer = 0; layer < mapTiles.size(); layer++) {
		SDL_Texture *layerTexture = NULL;
		
		//Create a black texture on the bottom layer
		if (layer == 0) {
			layerTexture = win->createTexture(width * getTileWidth(), height * getTileHeight());
		}

		//Create a transparent texture for all other layers
		else {
			layerTexture = win->createTransparentTexture(width * getTileWidth(), height * getTileHeight());
		}

		//Change the render target to the layer texture
		win->setRenderTarget(layerTexture);

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (mapTiles[layer][x][y] - 1 < 0) continue;
				Tile *currTile = getTileset()->getTile(mapTiles[layer][x][y] - 1);
				SDL_Rect src = Util::createRect(currTile->getRow() * getTileWidth(),
					currTile->getColumn() * getTileHeight(),
					getTileWidth(),
					getTileHeight());
				SDL_Rect dst = Util::createRect(x * getTileWidth(),
					y * getTileHeight(),
					getTileWidth(),
					getTileHeight());
				tilesetSprite->setSrcRect(src);
				tilesetSprite->setDstRect(dst);
				tilesetSprite->draw(win->getWindowRenderer());
				currTile = NULL;
			}
		}


		//Set the render target back to the window texture
		win->resetRenderTarget();

		mapTextures.push_back(layerTexture);
	}
	
	win = NULL;
	delete tilesetSprite;
	tilesetSprite = NULL;
}

Tileset * Map::getTileset() const { return tileset; }
unsigned int Map::getNumberOfLayers() const { return mapTextures.size(); }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
int Map::getTileWidth() const { return getTileset()->getTile(0) == NULL ? 0 : getTileset()->getTileWidth(); } 
int Map::getTileHeight() const { return getTileset()->getTile(0) == NULL ? 0 : getTileset()->getTileHeight(); }
std::vector<int **> Map::getLayersAsArray() const { return mapTiles; }
SDL_Texture * Map::getLayer(unsigned int layer) const { return layer < mapTextures.size() ? mapTextures[layer] : NULL; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::addLayer(int **tiles) { this->mapTiles.push_back(tiles); }
