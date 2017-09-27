#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include <vector>
#include <string>

class Tileset;
class Map;
struct Tag;

class MapLoader {
public:
	static MapLoader * getInstance();
	static void deleteInstance();

	Map * loadMap(const char *pathToMap);
    void loadTilesets(const char *pathToRes);

private:
	MapLoader();
	~MapLoader();
	static MapLoader *instance;

	void loadNextTileset(const char *pathToTileset);
	void populateMapInfo(Tag *tag, Map *map);
	std::vector<Tileset *> tilesets;
};

#endif
