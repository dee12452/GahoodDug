#include "Character.hpp"
#include "../util/Utils.hpp"
#include "../sprite/Sprites.hpp"

Character::Character(Map *map, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed)
    : BaseMovementObject(map, spriteSheet, movementUpdateTime, movementSpeed) {
    changeDirection(FacingDirection::DOWN);
    getSprite()->setDstW(Constants::CHARACTER_WIDTH);
    getSprite()->setDstH(Constants::CHARACTER_HEIGHT);
}

Character::~Character() {
}

void Character::onTickInBackground() {}

void Character::onMove(float percentToNextTile) {
	if (percentToNextTile < 0.5f) return;

	if (isWalkingLeft()) {
		getSprite()->setSrcX(Constants::CHARACTER_WIDTH);
	}
	else {
		getSprite()->setSrcX(Constants::CHARACTER_WIDTH * 3);
	}
}

void Character::onMoveEnd(FacingDirection direction) {
	getSprite()->setSrcX(0);
}

void Character::onChangeDirection(FacingDirection direction) {
	getSprite()->setSrcRect(Util::createRect(0,
		static_cast<int>(direction) * Constants::CHARACTER_HEIGHT,
		Constants::CHARACTER_WIDTH,
		Constants::CHARACTER_HEIGHT));
}
