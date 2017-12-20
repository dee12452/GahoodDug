#include "MapLoader.hpp"

#include <string>
#include <SDL2/SDL.h>
#include "Maps.hpp"
#include "../util/Utils.hpp"
#include "../util/XMLParser.hpp"

MapLoader * MapLoader::instance = NULL;

MapLoader * MapLoader::getInstance() {
	if (instance == NULL) {
		instance = new MapLoader();
	}
	return instance;
}

void MapLoader::deleteInstance() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
	}
}

MapLoader::MapLoader() {}

MapLoader::~MapLoader() {
    for(std::map<std::string, Map *>::const_iterator iterator = maps.begin(); iterator != maps.end(); ++iterator) {
        if(iterator->second != NULL) {
            delete iterator->second;
        }
    }
    maps.clear();
	
    for (unsigned int i = 0; i < tilesets.size(); i++) {
		if (tilesets[i] != NULL) {
			delete tilesets[i];
			tilesets[i] = NULL;
		}
	}
	tilesets.clear();
}

Map * MapLoader::getMap(const std::string &mapId) const {
    std::map<std::string, Map *>::const_iterator iterator = maps.find(mapId);
    Map *map = NULL;
    if(iterator != maps.end()) {
        map = iterator->second;
    }
    return map;
}

void MapLoader::loadAll(Game *game, const char *pathToResFolder) {
    std::vector<std::string> tilesetFiles = FileUtil::getFilesRecursively(pathToResFolder, Constants::TILESET_FILE_EXTENSION);
    if(tilesetFiles.size() == 0) { 
		Util::fatalError("Warning: Failed to find tilesets in given res folder"); 
	}
    for(size_t i = 0; i < tilesetFiles.size(); i++) {
        loadTileset(tilesetFiles[i].c_str());
        Util::log(SDL_LOG_PRIORITY_INFO, "Successfully loaded tileset " + tilesetFiles[i]);
    }
    std::vector<std::string> maps = FileUtil::getFilesRecursively(pathToResFolder, Constants::MAP_FILE_EXTENSION);
    for(size_t i = 0; i < tilesetFiles.size(); i++) {
        loadMap(game, maps[i].c_str());
        Util::log(SDL_LOG_PRIORITY_INFO, "Successfully loaded map " + maps[i]);
    }
}

void MapLoader::loadTileset(const char *pathToTileset) {
	XMLObject *obj = XMLParser::loadXML(pathToTileset);
	if (obj == NULL) {
		Util::fatalError("Failed to load tileset");
	}
	Tileset *tileset = new Tileset();
	int tileColumns = 0;
	if (obj->tags.size() > 0) {
        int width, height;

		//Load the name and number of columns of the tileset
		for (unsigned int i = 0; i < obj->tags[0]->attributes.size(); i++) {
            if (obj->tags[0]->attributes[i].first == "name") {
				tileset->setName(obj->tags[0]->attributes[i].second);
			}
			else if (obj->tags[0]->attributes[i].first == "columns") {
				tileColumns = std::stoi(obj->tags[0]->attributes[i].second);
			}
            else if(obj->tags[0]->attributes[i].first == "tilewidth") {
                width = std::stoi(obj->tags[0]->attributes[i].second);
            }
            else if(obj->tags[0]->attributes[i].first == "tileheight") {
                height = std::stoi(obj->tags[0]->attributes[i].second);
            }
		}
        tileset->setTileWidth(width);
        tileset->setTileHeight(height);
		int row = 0, x = 0;

		for (unsigned int i = 0; i < obj->tags[0]->subTags.size(); i++) {
			Tag *tag = obj->tags[0]->subTags[i];

			//Load the tileset image src
			if (tag->id == "image") {
				for (unsigned int j = 0; j < tag->attributes.size(); j++) {
					if (tag->attributes[j].first == "source") {
						tileset->setImageFile(FileUtil::getFileName(tag->attributes[j].second.substr(9).c_str()).c_str());
						break;
					}
				}
			}
			else if (tag->id == "tile") {
				int id;
				std::string type;
                for (unsigned int j = 0; j < tag->attributes.size(); j++) {
					if (tag->attributes[j].first == "id") {
						id = std::stoi(tag->attributes[j].second);
					}
					else if (tag->attributes[j].first == "type") {
						type = tag->attributes[j].second;
					}
				}
                tileset->addTile(new Tile(type,
					id,
					x,
					row));
				x++;
				if (x % tileColumns == 0) {
					row++; x = 0;
				}
			}
			tag = NULL;
		}
	}
	tilesets.push_back(tileset);
	XMLParser::destroyXMLObject(obj);
	obj = NULL;
}

void MapLoader::loadMap(Game *game, const char *path) {
	Map *map = new Map();
	XMLObject *obj = XMLParser::loadXML(path);
	if (obj == NULL) {
		Util::fatalError("Failed to load map");
	}
	for (unsigned int i = 0; i < obj->tags.size(); i++) {
		populateMapInfo(obj->tags[i], map);
	}
	XMLParser::destroyXMLObject(obj);
	map->generate(game);
	maps.insert(std::pair<std::string, Map *> (FileUtil::getFileName(path), map));
}

void MapLoader::populateMapInfo(Tag *tag, Map *map) {
    if(tag == NULL)
        return;

    //Get map width and height
    if (tag->id == "map") {
		for (unsigned int i = 0; i < tag->attributes.size(); i++) {
			if (tag->attributes[i].first == "width") {
				map->setWidth(std::stoi(tag->attributes[i].second));
			}
			else if (tag->attributes[i].first == "height") {
				map->setHeight(std::stoi(tag->attributes[i].second));
			}
		}
	}
    
    //Find the corresponding tileset
	else if (tag->id == "tileset") {
		for (unsigned int i = 0; i < tag->attributes.size(); i++) {
			if (tag->attributes[i].first == "source") {
				std::string ts = tag->attributes[i].second;
				for (unsigned int j = 0; j < tilesets.size(); j++) {
					if ("../tileset/" + tilesets[j]->getName() + ".tsx" == ts) {
						map->setTileset(tilesets[j]);
					}
				}
				break;
			}
		}
		if (map->getTileset() == NULL) {
			Util::fatalError("Failed to find a tileset for the map");
		}
	}

	//Find the maps that border the map
	else if (tag->id == "property") {
		MapDirection dir;
		const char *borderMap = "";
		for (unsigned int i = 0; i < tag->attributes.size(); i++) {
			if (tag->attributes[i].first == "name") {
				if (tag->attributes[i].second == "north_border") { dir = MapDirection::MAP_NORTH; }
				if (tag->attributes[i].second == "south_border") { dir = MapDirection::MAP_SOUTH; }
				if (tag->attributes[i].second == "east_border") { dir = MapDirection::MAP_EAST; }
				if (tag->attributes[i].second == "west_border") { dir = MapDirection::MAP_WEST; }
			}
			else if (tag->attributes[i].first == "value") { borderMap = tag->attributes[i].second.c_str(); }
		}
		map->setBorderingMap(dir, borderMap);
	}

    //Load width, height, and data for each layer
	else if (tag->id == "layer") {
        int **layer = NULL;
		int lwidth = 0, lheight = 0;
		for (unsigned int i = 0; i < tag->attributes.size(); i++) {
			if (tag->attributes[i].first == "width") {
				lwidth = std::stoi(tag->attributes[i].second);
				layer = new int*[lwidth];
			}
			else if (tag->attributes[i].first == "height") {
				lheight = std::stoi(tag->attributes[i].second);
				if (layer != NULL) {
					for (int j = 0; j < lwidth; j++) {
						layer[j] = new int[lheight];
					}
				}
			}
		}
		if (tag->subTags.size() > 0 
			&& tag->subTags[0] != NULL
			&& tag->subTags[0]->id == "data") {
			std::string tileData = tag->subTags[0]->data;
            std::string nextInt = "";
            int currRow = 0, currCol = 0;
            for(unsigned int i = 0; i < tileData.size(); i++) {
                //using ASCII, 
                //check to see if the next char is a number
                int nextChar = (int)tileData[i] - (int) '0';
                if(nextChar < 10 && nextChar >= 0) {
                    nextInt += (char) (nextChar + '0');
                }
                else if(nextInt != "") {
                    layer[currRow][currCol] = std::stoi(nextInt);
                    currRow++;
                    if(currRow == lwidth) {
                        currRow = 0;
                        currCol++;
                    }
                    if(currCol == lheight)
                        break;
                    nextInt = "";
                }
            }
            map->addLayer(layer);
		}
	}

    for(unsigned int i = 0; i < tag->subTags.size(); i++) {
        populateMapInfo(tag->subTags[i], map);
    }
}
