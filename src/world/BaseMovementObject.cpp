#include "BaseMovementObject.hpp"
#include "../util/Timer.hpp"
#include "../sprite/Sprite.hpp"
#include "../util/Utils.hpp"

BaseMovementObject::BaseMovementObject(SpriteSheet *spriteSheet, 
	int tileW, 
	int tileH, 
	int movementUpdateTime, 
	int movementSpeed) : BaseWorldObject(spriteSheet),
	displacement(0),
	moveSpeed(movementSpeed),
	nextDirection(NONE),
	movementTimer(new Timer(movementUpdateTime)),
	moving(false),
	walkLeft(true) {}

BaseMovementObject::~BaseMovementObject() {
	if (movementTimer != NULL) {
		delete movementTimer;
		movementTimer = NULL;
	}
}

void BaseMovementObject::move(FacingDirection direction) {
	if (moving) {
		nextDirection = direction;
	}
	else {
		changeDirection(direction);
		moving = true;
	}
}

void BaseMovementObject::cancelNextMove() { nextDirection = NONE; }

void BaseMovementObject::changeDirection(FacingDirection direction) {
	if (direction == NONE || isMoving()) return;
	currentDirection = direction;
	onChangeDirection(direction);
}

bool BaseMovementObject::isMoving() const { return moving; }
FacingDirection BaseMovementObject::getCurrentDirection() const { return currentDirection; }
FacingDirection BaseMovementObject::getNextDirection() const { return nextDirection; }