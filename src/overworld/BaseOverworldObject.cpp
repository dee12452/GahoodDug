#include "../headers/BaseOverworldObject.hpp"

#include <SDL2/SDL_rect.h>
#include "../headers/Constants.hpp"

BaseOverworldObject::BaseOverworldObject(const std::string &id, int sX, int sY, int sW, int sH) 
	: BaseGameObject(id, sX, sY, sW, sH, 0, 0, 0, 0) {
	mapX = 0; mapY = 0;
	prevMapX = 0; prevMapY = 0;
	setVisible(true);
	SDL_Rect drawDst;
	drawDst.x = 0; drawDst.y = 0;
	int tileW = Constants::WINDOW_WIDTH / Constants::MAP_NUM_TILES_WIDTH;
	int tileH = Constants::WINDOW_WIDTH / Constants::MAP_NUM_TILES_HEIGHT;
	drawDst.w = (sW * tileW) / Constants::SPRITE_TILE_WIDTH;
	drawDst.h = (sH * tileW) / Constants::SPRITE_TILE_HEIGHT;
	setDestinationRect(drawDst);
}

BaseOverworldObject::~BaseOverworldObject() {}

int BaseOverworldObject::getMapX() const { return mapX; }
int BaseOverworldObject::getMapY() const { return mapY; }
int BaseOverworldObject::getPrevMapX() const { return prevMapX; }
int BaseOverworldObject::getPrevMapY() const { return prevMapY; }
bool BaseOverworldObject::isVisible() const { return visible; }

void BaseOverworldObject::setMapX(int x) { prevMapX = mapX; mapX = x; }
void BaseOverworldObject::setMapY(int y) { prevMapY = mapY; mapY = y; }
void BaseOverworldObject::setVisible(bool v) { 
	visible = v; 
	if (visible) {
		setAlpha(Constants::SPRITE_ALPHA_FULL);
	}
	else {
		setAlpha(Constants::SPRITE_ALPHA_NONE);
	}
}