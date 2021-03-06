#ifndef TILE_HPP
#define TILE_HPP

#include <string>

class Tile {
public:
    Tile(const std::string &tType, int tId, int row, int column);

    ~Tile();

	int getId() const;
	std::string getTileType() const;
    int getRow() const;
    int getColumn() const;

private:
	int tileId, tileRow, tileColumn;
	std::string tileType;
};

#endif
