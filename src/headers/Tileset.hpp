#ifndef TILE_SET_HPP
#define TILE_SET_HPP

#include <vector>
#include <string>

class Tile;

class Tileset {
public: 
	Tileset(const std::string &, 
		const std::string &, 
		int, 
		int,
		const std::vector<Tile *> &);
	~Tileset();

	Tile * getTile(int) const;
	std::string getName() const;
	std::string getImage() const;
	int getWidth() const;
	int getHeight() const;

private:
	std::string name;
	std::string tilesetImageId;
	int width;
	int height;
	std::vector<Tile *> tiles;
};

#endif
