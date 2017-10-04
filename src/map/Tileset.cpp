#include "Tileset.hpp"

#include "Tile.hpp"
#include <string.h>

Tileset::Tileset() {
    imageFilePath = NULL;
}

Tileset::Tileset(const std::string &name,
    const char *imgPath,
	int w,
	int h,
    int tW,
    int tH,
	const std::vector<Tile *> &tiles) 
        : tilesetName(name), width(w), height(h), tileWidth(tW), tileHeight(tH), tiles(tiles) {
    setImageFile(imgPath);
}

Tileset::~Tileset() {
	for (unsigned int i = 0; i < tiles.size(); i++) {
		if (tiles[i] != NULL) {
			delete tiles[i];
			tiles[i] = NULL;
		}
	}
	tiles.clear();
    if(imageFilePath != NULL) {
        delete[] imageFilePath;
        imageFilePath = NULL;
    }
}

void Tileset::addTile(Tile *tile) { tiles.push_back(tile); }
void Tileset::setDimensions(int w, int h) { width = w; height = h; }
void Tileset::setName(const std::string &name) { tilesetName = name; }
void Tileset::setImageFile(const char *imgPath) {
	int pathLength = 0;
    while(imgPath[pathLength] != '\0') pathLength++;
    pathLength += 2;
    this->imageFilePath = new char[pathLength];
    strcpy(imageFilePath, imgPath);
}
void Tileset::setTileWidth(int tW) { tileWidth = tW; }
void Tileset::setTileHeight(int tH) { tileHeight = tH; }

char * Tileset::getImagePath() const { return imageFilePath; }
Tile * Tileset::getTile(unsigned int index) const { return index >= tiles.size() ? NULL : tiles[index]; }
int Tileset::getHeight() const { return height; }
int Tileset::getWidth() const { return width; }
int Tileset::getTileWidth() const { return tileWidth; }
int Tileset::getTileHeight() const { return tileHeight; }
std::string Tileset::getName() const { return tilesetName; }
