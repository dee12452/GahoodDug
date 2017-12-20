#include "Map.hpp"
#include "Tileset.hpp"
#include "Tile.hpp"

#include "../util/Constants.hpp"
#include "../game/Game.hpp"
#include "../util/Util.hpp"
#include "../sprite/Sprites.hpp"
#include "MapLoader.hpp"

Map::Map() :
	width(0), height(0), generated(false), tileset(NULL) {
	borderingMaps = new char *[4]{ NULL,NULL,NULL,NULL };
}

Map::Map(int w, int h, std::vector<int **>tileCoords, Tileset *tileset) :
	width(w), height(h), generated(false), mapTiles(tileCoords), tileset(tileset) {
	borderingMaps = new char *[4]{ NULL,NULL,NULL,NULL };
}

Map::~Map() {
	//Delete the bordering maps information
	for (int i = 0; i < 0; i++) if (borderingMaps[i] != NULL) delete[] borderingMaps[i];
	delete[] borderingMaps; borderingMaps = NULL;

	//Clear the map tiles
	for (unsigned int j = 0; j < mapTiles.size(); j++) {
		for (int i = 0; i < width; i++) {
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
                if(currTile == NULL) Util::fatalError("Current tile is null while generating map");
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

Tile * Map::getTile(unsigned int layer, int tileX, int tileY) const {
    if(layer > getNumberOfLayers() || tileX > getWidth() || tileY > getHeight()) return NULL;
    return getTileset()->getTile(mapTiles[layer][tileX][tileY] - 1); 
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
void Map::setBorderingMap(MapDirection direction, const char *map) {
	int size = 0; while (map[size] != '\0') size++; int dir = static_cast<int>(direction);
	borderingMaps[dir] = new char[size + 1];
	strcpy(borderingMaps[dir], map);
}
Map * Map::getBorderingMap(MapDirection direction) const {
	return borderingMaps[static_cast<int>(direction)] == NULL ? NULL : MapLoader::getInstance()->getMap(borderingMaps[static_cast<int>(direction)]);
}
