#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
struct SDL_Renderer;

class Map {
public:
	Map();
	Map(int, int, int **, Tileset *);
	~Map();

	Tileset * getTileset() const;
	int getWidth() const;
	int getHeight() const;

	void setTileset(Tileset *);
	void setWidth(int);
	void setHeight(int);
	void setTiles(int **);

	void draw(SDL_Renderer *);
	void update();

private:
	int width;
	int height;
	int **mapTiles;
	Tileset *tileset;
};

#endif