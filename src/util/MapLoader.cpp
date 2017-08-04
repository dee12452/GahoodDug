#include "../headers/MapLoader.hpp"

#include <string>
#include <SDL2/SDL.h>
#include "../headers/FileUtil.hpp"
#include "../headers/XMLParser.hpp"
#include "../headers/Map.hpp"
#include "../headers/Tileset.hpp"
#include "../headers/Tile.hpp"
#include "../headers/Util.hpp"
#include "../headers/Constants.hpp"

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
	for (unsigned int i = 0; i < tilesets.size(); i++) {
		if (tilesets[i] != NULL) {
			delete tilesets[i];
			tilesets[i] = NULL;
		}
	}
	tilesets.clear();
	tilesetFiles.clear();
}

void MapLoader::setTilesetFolder(const char *path) {
	tilesetFiles = FileUtil::getFiles(path);
}

bool MapLoader::hasLoadedAllTilesets() const {
	return tilesetFiles.size() == tilesets.size();
}

void MapLoader::loadNextTileset() {
	XMLObject *obj = XMLParser::loadXML((Constants::GAME_TILESET_FOLDER + tilesetFiles[tilesets.size()]).c_str());
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
						tileset->setImage(tag->attributes[j].second.substr(9));
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
				if (id % tileColumns == 0) {
					row++; x = 0;
				}
				tileset->addTile(new Tile(tileset->getImage(),
					type,
					id,
					row * Constants::TILE_WIDTH,
					x * Constants::TILE_HEIGHT,
					true));
				x++;
			}
			tag = NULL;
		}
	}
	tilesets.push_back(tileset);
	XMLParser::destroyXMLObject(obj);
	obj = NULL;
}

Map * MapLoader::loadMap(const char *path) {
	Map *map = new Map();
	XMLObject *obj = XMLParser::loadXML(path);
	int timeout = 0;
	const int MAX_TIMEOUT = 1000;
	while (!hasLoadedAllTilesets()) {
		SDL_Delay(Constants::RENDER_LOOP_DELAY);
		timeout++;
		if (timeout > MAX_TIMEOUT) {
			Util::fatalError("Timed out trying to load tilesets");
		}
	}
	if (obj == NULL) {
		Util::fatalError("Failed to load map");
	}
	for (unsigned int i = 0; i < obj->tags.size(); i++) {
		populateMapInfo(obj->tags[i], map);
	}
	XMLParser::destroyXMLObject(obj);
	return map;
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
