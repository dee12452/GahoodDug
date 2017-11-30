#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
class Game;
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
	int getTileWidth() const;
    int getTileHeight() const;
	unsigned int getNumberOfLayers() const;
    std::vector<int **> getLayersAsArray() const;
	SDL_Texture * getLayer(unsigned int layer) const;

	void setTileset(Tileset *tileset);
	void setWidth(int width);
	void setHeight(int height);
	void addLayer(int **layer);

	//Generate the map from the information given to the map
	void generate(Game *game);

private:
	int width;
	int height;
	bool generated;
	std::vector<int **> mapTiles;
	std::vector<SDL_Texture *> mapTextures;
	Tileset *tileset;
};

#endif
