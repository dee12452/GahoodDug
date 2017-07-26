#include "../headers/Tileset.hpp"

#include "../headers/Tile.hpp"

Tileset::Tileset(const std::string &name,
	const std::string &imageSource,
	int w,
	int h,
	const std::vector<Tile *> &tiles) {
	this->name = name;
	this->width = w;
	this->height = h;
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
}

Tile * Tileset::getTile(unsigned int index) const { return index >= tiles.size() ? NULL : tiles[index]; }
int Tileset::getHeight() const { return height; }
int Tileset::getWidth() const { return width; }
std::string Tileset::getImage() const { return tilesetImageId; }
std::string Tileset::getName() const { return name; }
