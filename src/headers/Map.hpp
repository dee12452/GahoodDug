#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
struct SDL_Renderer;

class Map {
public:
	Map();
	Map(int, int, std::vector<int **>, Tileset *);
	~Map();

	Tileset * getTileset() const;
	int getWidth() const;
	int getHeight() const;
	std::vector<int **> getLayers() const;

	void setTileset(Tileset *);
	void setWidth(int);
	void setHeight(int);
	void addLayer(int **);

	void draw(SDL_Renderer *);
	void update();

private:
	int width;
	int height;
	std::vector<int **> mapLayers;
	Tileset *tileset;
};

#endif