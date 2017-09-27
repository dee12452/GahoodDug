#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
class Window;
struct SDL_Texture;

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
	std::vector<SDL_Texture *> mapLayers;
	Tileset *tileset;
};

#endif
