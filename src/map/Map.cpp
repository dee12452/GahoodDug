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
		for (int i = 0; i < width / tileset->getTile(0)->getWidth(); i++) {
			delete[] mapTiles[j][i];
			mapTiles[j][i] = NULL;
		}
		delete[] mapTiles[j];
		mapTiles[j] = NULL;
	}
	
	//Map loader will handle deletion of tilesets
	tileset = NULL;
}


/* 
 * May need this laterm but this puts the map into a texture.
void Map::generate(Window *) {	
    //If there is already a map or the tileset image hasn't loaded, don't generate the map
	if (mapLayers.size() > 0 || ImageLoader::getInstance()->getImage(tileset->getImage()) == NULL) return;
	
	for (unsigned int layer = 0; layer < mapTiles.size(); layer++) {
		SDL_Texture *layerTexture = win->createTransparentTexture(
			Constants::SPRITE_TILE_WIDTH * width,
			Constants::SPRITE_TILE_HEIGHT * height
		);
		win->setRenderTarget(layerTexture);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (mapTiles[layer][j][i] - 1 < 0) continue;
				Tile *currTile = tileset->getTile(mapTiles[layer][j][i] - 1);
				SDL_Rect dst;
				dst.x = j * Constants::SPRITE_TILE_WIDTH;
				dst.y = i * Constants::SPRITE_TILE_HEIGHT;
				dst.w = Constants::SPRITE_TILE_WIDTH;
				dst.h = Constants::SPRITE_TILE_HEIGHT;
				currTile->setDestinationRect(dst);
				currTile->draw(win);
			}
		}
		mapLayers.push_back(layerTexture);
	}
	win->resetRenderTarget();
}
*
*/

Tileset * Map::getTileset() const { return tileset; }
int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
std::vector<int **> Map::getLayers() const { return mapTiles; }

void Map::setTileset(Tileset *ts) { this->tileset = ts; }
void Map::setWidth(int w) { this->width = w; }
void Map::setHeight(int h) { this->height = h; }
void Map::addLayer(int **tiles) { this->mapTiles.push_back(tiles); }

