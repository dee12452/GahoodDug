#include "../headers/BaseGameObject.hpp"

BaseGameObject::BaseGameObject(const std::string &id) 
	: Sprite(id) {}

BaseGameObject::BaseGameObject(const std::string &id, int sX, int sY, int sW, int sH, int dX, int dY, int dW, int dH)
	: Sprite(id, sX, sY, sW, sH, dX, dY, dW, dH) {}

BaseGameObject::BaseGameObject(const std::string &id, const SDL_Rect &srcR, const SDL_Rect &dstR)
	: Sprite(id, srcR, dstR) {}

BaseGameObject::~BaseGameObject() {}