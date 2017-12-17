#include "BaseWorldObject.hpp"
#include "../map/Map.hpp"
#include "../sprite/Sprites.hpp"

BaseWorldObject::BaseWorldObject(Map *map, SpriteSheet *spriteSheet) : 
    map(map),
    layer(0), 
    objectSprite(spriteSheet->createSprite()) {
	setTileX(0);
	setTileY(0);
}

BaseWorldObject::~BaseWorldObject() {
    if(objectSprite != NULL) {
        delete objectSprite;
        objectSprite = NULL;
    }
}

void BaseWorldObject::setTileX(int x) { 
	tileX = x; 
	posX = tileX * map->getTileWidth(); 
}
void BaseWorldObject::setTileY(int y) { 
	tileY = y; 
	posY = tileY * map->getTileHeight();
}
void BaseWorldObject::setPositionX(int x) { 
	posX = x; 
	if(posX == 0 || map->getTileWidth() == 0) setTileX(0);
	else tileX = posX / map->getTileWidth();
}
void BaseWorldObject::setPositionY(int y) { 
	posY = y;
	if (posY == 0 || map->getTileHeight() == 0) setTileY(0);
	else tileY = posY / map->getTileHeight();
}
void BaseWorldObject::setLayer(int newLayer) { layer = newLayer; }


int BaseWorldObject::getTileX() const { return tileX; }
int BaseWorldObject::getTileY() const { return tileY; }
int BaseWorldObject::getPositionX() const { return posX; }
int BaseWorldObject::getPositionY() const { return posY; }
int BaseWorldObject::getLayer() const { return layer; }
Sprite * BaseWorldObject::getSprite() const { return objectSprite; }
