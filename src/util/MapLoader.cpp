#include "../headers/MapLoader.hpp"

#include <string>
#include "../headers/XMLParser.hpp"
#include "../headers/Map.hpp"
#include "../headers/Tileset.hpp"
#include "../headers/Util.hpp"

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
}

Map * MapLoader::loadMap(const char *path) {
	Map *map = new Map();
	XMLObject *obj = XMLParser::loadXML(path);
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
	else if (tag->id == "tileset") {

	}
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
		}
	}
}