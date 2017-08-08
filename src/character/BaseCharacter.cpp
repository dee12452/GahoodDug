#include "../headers/BaseCharacter.hpp"

const unsigned int BaseCharacter::updateTime = 100;

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

bool BaseCharacter::move(const CharacterDirection &direction, unsigned int duration) {
	if (moving) return false;
	moving = true;
	changeFacingDirection(direction);
	return true;
}

void BaseCharacter::onUpdate() {
	if (moving) {
		switch (currentDirection) {
		case CH_UP:
			break;
		case CH_DOWN:
			break;
		case CH_LEFT:
			break;
		case CH_RIGHT:
			break;
		}
	}
}