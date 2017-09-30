#include "Tile.hpp"

#include <SDL2/SDL_rect.h>
#include "../util/Constants.hpp"
#include "../util/Timer.hpp"

Tile::Tile(const std::string &tType, int tId, int row, int column, int width, int height) {
	tileId = tId;
	tileType = tType;
    tileRow = row;
    tileColumn = column;
    tileWidth = width;
    tileHeight = height;
}

Tile::~Tile() {}

int Tile::getId() const { return this->tileId; }
std::string Tile::getTileType() const { return this->tileType; }
int Tile::getRow() const { return this->tileRow; }
int Tile::getColumn() const { return this->tileColumn; }
int Tile::getWidth() const { return this->tileWidth; }
int Tile::getHeight() const { return this->tileHeight; }
