#include "Tile.hpp"

Tile::Tile(const std::string &tType, int tId, int row, int column) 
    : tileId(tId), tileRow(row), tileColumn(column), tileType(tType) {
}

Tile::~Tile() {}

int Tile::getId() const { return this->tileId; }
std::string Tile::getTileType() const { return this->tileType; }
int Tile::getRow() const { return this->tileRow; }
int Tile::getColumn() const { return this->tileColumn; }
