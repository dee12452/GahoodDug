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
	const std::vector<Tile *> &tiles) {
    tilesetName = name;
    setImageFile(imgPath);
    width = w;
	height = h;
	this->tiles = tiles;
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

char * Tileset::getImagePath() const { return imageFilePath; }
Tile * Tileset::getTile(unsigned int index) const { return index >= tiles.size() ? NULL : tiles[index]; }
int Tileset::getHeight() const { return height; }
int Tileset::getWidth() const { return width; }
std::string Tileset::getName() const { return tilesetName; }
