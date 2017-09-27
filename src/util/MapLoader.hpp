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

	Map * loadMap(const char *);

	void setTilesetFolder(const char *);
	bool hasLoadedAllTilesets() const;
	void loadNextTileset();

private:
	MapLoader();
	~MapLoader();
	static MapLoader *instance;

	void populateMapInfo(Tag *, Map *);
	std::vector<Tileset *> tilesets;
	std::vector<std::string> tilesetFiles;
};

#endif
