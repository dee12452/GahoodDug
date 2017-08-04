#ifndef TILE_SET_HPP
#define TILE_SET_HPP

#include <vector>
#include <string>

class Tile;

class Tileset {
public: 
	Tileset();
	Tileset(const std::string &, 
		const std::string &, 
		int, 
		int,
		const std::vector<Tile *> &);
	~Tileset();

	void setDimensions(int, int);
	void setName(const std::string &);
	void setImage(const std::string &);
	void addTile(Tile *);

	Tile * getTile(unsigned int) const;
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
