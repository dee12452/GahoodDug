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

void MapLoader::loadAll(const char *pathToResFolder) {
    std::vector<std::string> tilesetFiles = FileUtil::getFilesRecursively(pathToResFolder, Constants::TILESET_FILE_EXTENSION);
    if(tilesetFiles.size() == 0) {
        Util::print("Warning: Failed to find tilesets in given res folder");
        return;
    }
    for(size_t i = 0; i < tilesetFiles.size(); i++) {
        loadTileset(tilesetFiles[i].c_str());
        Util::log("Successfully loaded tileset " + tilesetFiles[i]);
    }
    std::vector<std::string> maps = FileUtil::getFilesRecursively(pathToResFolder, Constants::MAP_FILE_EXTENSION);
    for(size_t i = 0; i < tilesetFiles.size(); i++) {
        loadMap(maps[i].c_str());
        Util::log("Successfully loaded map " + maps[i]);
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
		//Load the name and number of columns of the tileset
		for (unsigned int i = 0; i < obj->tags[0]->attributes.size(); i++) {
            if (obj->tags[0]->attributes[i].first == "name") {
				tileset->setName(obj->tags[0]->attributes[i].second);
			}
			else if (obj->tags[0]->attributes[i].first == "columns") {
				tileColumns = std::stoi(obj->tags[0]->attributes[i].second);
			}
		}
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
				int id, width, height;
				std::string type;
                for (unsigned int j = 0; j < tag->attributes.size(); j++) {
					if (tag->attributes[j].first == "id") {
						id = std::stoi(tag->attributes[j].second);
					}
					else if (tag->attributes[j].first == "type") {
						type = tag->attributes[j].second;
					}
                    else if(tag->attributes[j].first == "tilewidth") {
                        width = std::stoi(tag->attributes[j].second);
                    }
                    else if(tag->attributes[j].first == "tileheight") {
                        height = std::stoi(tag->attributes[j].second);
                    }
				}
                tileset->addTile(new Tile(type,
					id,
					x,
					row,
                    width,
                    height));
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

void MapLoader::loadMap(const char *path) {
	Map *map = new Map();
	XMLObject *obj = XMLParser::loadXML(path);
	if (obj == NULL) {
		Util::fatalError("Failed to load map");
	}
	for (unsigned int i = 0; i < obj->tags.size(); i++) {
		populateMapInfo(obj->tags[i], map);
	}
	XMLParser::destroyXMLObject(obj);
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
