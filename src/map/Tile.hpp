#ifndef TILE_HPP
#define TILE_HPP

#include <string>

class Tile {
public:
    Tile(const std::string &tType, int tId, int row, int column, int  width, int height);

    ~Tile();

	int getId() const;
	std::string getTileType() const;
    int getRow() const;
    int getColumn() const;
    int getWidth() const;
    int getHeight() const;

private:
	int tileId, tileRow, tileColumn, tileWidth, tileHeight;
	std::string tileType;
};

#endif
