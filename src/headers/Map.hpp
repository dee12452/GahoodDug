#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Tileset;
class Window;
class BaseCharacter;
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

	BaseCharacter * getPlayer() const;

private:
	int width;
	int height;
	std::vector<int **> mapTiles;
	std::vector<SDL_Texture *> mapLayers;
	Tileset *tileset;
	BaseCharacter *playerCharacter;
};

#endif