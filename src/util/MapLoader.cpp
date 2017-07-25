#include "../headers/MapLoader.hpp"
#include "../headers/XMLParser.hpp"
#include "../headers/Map.hpp"

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

			}
			else if (tag->attributes[i].first == "height") {

			}
		}
	}
}