#include "Tile.hpp"

#include <SDL2/SDL_rect.h>
#include "../util/Constants.hpp"
#include "../util/Timer.hpp"

Tile::Tile(const std::string &tType, int tId, int row, int column) {
	tileId = tId;
	tileType = tType;
    tileRow = row;
    tileColumn = column;
}

Tile::~Tile() {}

int Tile::getTileId() const { return this->tileId; }
std::string Tile::getTileType() const { return this->tileType; }
int Tile::getTileRow() const { return this->tileRow; }
int Tile::getTileColumn() const { return this->tileColumn; }
