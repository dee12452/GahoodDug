#ifndef TILE_SET_HPP
#define TILE_SET_HPP

#include <vector>
#include <string>

class Tile;

class Tileset {
public: 
	Tileset();
	Tileset(const std::string &name,
        const char *imgPath, 
		int w, 
		int h,
		const std::vector<Tile *> &tiles);
	~Tileset();

	void setDimensions(int w, int h);
	void setImageFile(const char *imgPath);
	void addTile(Tile *tile);
    void setName(const std::string &name);

	Tile * getTile(unsigned int) const;
	char * getImagePath() const;
	int getWidth() const;
	int getHeight() const;
    std::string getName() const;

private:
    std::string tilesetName;
    char *imageFilePath;
	int width;
	int height;
	std::vector<Tile *> tiles;
};

#endif
