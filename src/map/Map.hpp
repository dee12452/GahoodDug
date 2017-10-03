#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
class Window;
struct SDL_Texture;

typedef enum MapDirection { MAP_NORTH = 0, MAP_SOUTH = 1, MAP_EAST = 2, MAP_WEST = 3 } MapDirection;

class Map {
public:
	Map();
	Map(int width, int height, std::vector<int **> tileLayers, Tileset *tileset);
	~Map();

	Tileset * getTileset() const;
	int getWidth() const;
	int getHeight() const;
	std::vector<int **> getLayers() const;

	void setTileset(Tileset *tileset);
	void setWidth(int width);
	void setHeight(int height);
	void addLayer(int **layer);

private:
	int width;
	int height;
	std::vector<int **> mapTiles;
	Tileset *tileset;
};

#endif
