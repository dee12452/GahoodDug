#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
class Window;
struct SDL_Texture;

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

	void draw(Window *);
	void update();
	void generate(Window *);

private:
	int width;
	int height;
	std::vector<int **> mapLayers;
	Tileset *tileset;
	SDL_Texture *mapTexture;
};

#endif