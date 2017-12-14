#include "BaseWorldObject.hpp"
#include "../map/Map.hpp"
#include "../sprite/Sprites.hpp"

BaseWorldObject::BaseWorldObject(Map *map, SpriteSheet *spriteSheet) : 
    mapTileWidth(map->getTileWidth()),
	mapTileHeight(map->getTileHeight()),
	posX(0), 
    posY(0), 
    layer(0), 
    objectSprite(spriteSheet->createSprite()) {

}

BaseWorldObject::~BaseWorldObject() {
    if(objectSprite != NULL) {
        delete objectSprite;
        objectSprite = NULL;
    }
}

void BaseWorldObject::setTileX(int x) { 
	tileX = x; 
	posX = tileX * mapTileWidth; 
}
void BaseWorldObject::setTileY(int y) { 
	tileY = y; 
	posY = tileY * mapTileHeight;
}
void BaseWorldObject::setPositionX(int x) { 
	posX = x; 
	if(posX == 0 || mapTileWidth == 0) setTileX(0);
	else tileX = posX / mapTileWidth;
}
void BaseWorldObject::setPositionY(int y) { 
	posY = y;
	if (posY == 0 || mapTileHeight == 0) setTileY(0);
	else tileY = posY / mapTileHeight;
}
void BaseWorldObject::setLayer(int newLayer) { layer = newLayer; }


int BaseWorldObject::getTileX() const { return tileX; }
int BaseWorldObject::getTileY() const { return tileY; }
int BaseWorldObject::getPositionX() const { return posX; }
int BaseWorldObject::getPositionY() const { return posY; }
int BaseWorldObject::getLayer() const { return layer; }
Sprite * BaseWorldObject::getSprite() const { return objectSprite; }
