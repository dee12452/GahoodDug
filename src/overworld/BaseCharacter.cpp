#include "../headers/BaseCharacter.hpp"

#include <SDL2/SDL_rect.h>
#include "../headers/Util.hpp"
#include "../headers/Constants.hpp"

const __int64 BaseCharacter::updateTime = 25;
const __int64 BaseCharacter::defaultMoveTime = 325;

BaseCharacter::BaseCharacter(const std::string &id, int x, int y, int w, int h) 
	: BaseOverworldObject(id, x, y, w, h) {
	setUpdateTimer(updateTime);
	moving = false;
	walkLeft = false;
	currentLayer = 0;
	currentDirection = CH_NONE;
	nextDirection = CH_NONE;
}

BaseCharacter::~BaseCharacter() {}

CharacterDirection BaseCharacter::getFacingDirection() const {
	return currentDirection;
}

void BaseCharacter::changeFacingDirection(const CharacterDirection &direction) {
	if (currentDirection != direction) {
		currentDirection = direction;
		onChangeDirection(direction);
	}
}

bool BaseCharacter::isMoving() const {
	return moving;
}

uint8_t BaseCharacter::getCurrentMapLayer() const { return currentLayer;  }

void BaseCharacter::setCurrentMapLayer(uint8_t layer) { currentLayer = layer; }

bool BaseCharacter::move(const CharacterDirection &direction) { return move(direction, defaultMoveTime); }

bool BaseCharacter::move(const CharacterDirection &direction, unsigned int duration) {
	return false;
}

void BaseCharacter::cancelNextMove() { nextDirection = CH_NONE;  }

void BaseCharacter::onUpdate() {
}

void BaseCharacter::onMove(const CharacterDirection &dir, __int64 curr, __int64 total) {
}

void BaseCharacter::onMoveEnd(const CharacterDirection &, int, int) {
}

void BaseCharacter::onMoveStart(const CharacterDirection &dir) {
}

void BaseCharacter::onChangeDirection(const CharacterDirection &) {}