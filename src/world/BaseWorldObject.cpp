#include "BaseWorldObject.hpp"
#include "World.hpp"
#include "../game/Game.hpp"
#include "../map/Map.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Util.hpp"

BaseWorldObject::BaseWorldObject(World *world, SpriteSheet *image, int tickTime) :
	  BaseGameObject(tickTime),
      world(world),
      layer(0), 
      objectSprite(image->createSprite()) {
	if (objectSprite == NULL) Util::fatalError("Failed to create a world object sprite");
	SDL_Rect empty = Util::createRect(0, 0, 0, 0);
	setSourceRect(empty); setDestinationRect(empty);
	setTileX(0);
	setTileY(0);
}

BaseWorldObject::~BaseWorldObject() {
    if(objectSprite != NULL) {
        delete objectSprite;
        objectSprite = NULL;
    }
}

void BaseWorldObject::setRawX(int x) const { objectSprite->setDstX(x); }
void BaseWorldObject::setRawY(int y) const { objectSprite->setDstY(y); }
void BaseWorldObject::setWidth(int w) const { objectSprite->setDstW(w); }
void BaseWorldObject::setHeight(int h) const { objectSprite->setDstH(h); }
void BaseWorldObject::setTileX(int x) { 
	tileX = x; 
	posX = tileX * getWorld()->getMap()->getTileWidth(); 
}
void BaseWorldObject::setTileY(int y) { 
	tileY = y; 
	posY = tileY * getWorld()->getMap()->getTileHeight();
}
void BaseWorldObject::setPositionX(int x) { 
	posX = x; 
	if(posX == 0 || getWorld()->getMap()->getTileWidth() == 0) setTileX(0);
	else tileX = posX / getWorld()->getMap()->getTileWidth();
}
void BaseWorldObject::setPositionY(int y) { 
	posY = y;
	if (posY == 0 || getWorld()->getMap()->getTileHeight() == 0) setTileY(0);
	else tileY = posY / getWorld()->getMap()->getTileHeight();
}
void BaseWorldObject::setLayer(int newLayer) { layer = newLayer; }

void BaseWorldObject::onDraw(Window *win) { objectSprite->draw(win); }

int BaseWorldObject::getRawX() const { return objectSprite->getDstX(); }
int BaseWorldObject::getRawY() const { return objectSprite->getDstY(); }
int BaseWorldObject::getWidth() const { return objectSprite->getDstW(); }
int BaseWorldObject::getHeight() const { return objectSprite->getDstH(); }
int BaseWorldObject::getTileX() const { return tileX; }
int BaseWorldObject::getTileY() const { return tileY; }
int BaseWorldObject::getPositionX() const { return posX; }
int BaseWorldObject::getPositionY() const { return posY; }
int BaseWorldObject::getLayer() const { return layer; }
World * BaseWorldObject::getWorld() const { return world; }

void BaseWorldObject::setSourceRect(const SDL_Rect &srcRect) const { objectSprite->setSrcRect(srcRect); }
void BaseWorldObject::setDestinationRect(const SDL_Rect &dstRect) const { objectSprite->setDstRect(dstRect); }
SDL_Rect BaseWorldObject::getSourceRect() const {
	if (objectSprite->getSrcRect() != NULL) {
		return *objectSprite->getSrcRect();
	}
	return Util::createRect(0, 0, 0, 0);
}
SDL_Rect BaseWorldObject::getDestinationRect() const {
	if (objectSprite->getDstRect() != NULL) {
		return *objectSprite->getDstRect();
	}
	return Util::createRect(0, 0, 0, 0);
}

void BaseWorldObject::getImageDimensions(int &w, int &h) const { Util::querySpriteSourceImage(objectSprite, w, h); }

