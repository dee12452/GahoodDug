#include "BaseMovementObject.hpp"
#include "../util/Timer.hpp"
#include "../sprite/Sprite.hpp"
#include "../util/Utils.hpp"

BaseMovementObject::BaseMovementObject(Map *map, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed) 
	: BaseWorldObject(map, spriteSheet),
	displacement(0),
	moveSpeed(movementSpeed),
	nextDirection(NONE),
	movementTimer(new Timer(movementUpdateTime)),
	moving(false),
    canMove(false),
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

void BaseMovementObject::onTick(Game *) {
	if (moving && currentDirection != FacingDirection::NONE && movementTimer->check()) {
        if(canMove) {
            switch (currentDirection) {
            case FacingDirection::UP:
                setPositionY(getPositionY() - moveSpeed);
                break;
            case FacingDirection::DOWN:
                setPositionY(getPositionY() + moveSpeed);
                break;
            case FacingDirection::LEFT:
                setPositionX(getPositionX() - moveSpeed);
                break;
            case FacingDirection::RIGHT:
                setPositionX(getPositionX() + moveSpeed);
                break;
            default:
                break;
            }
        }
		displacement += moveSpeed;

		//left or right
		if (currentDirection == FacingDirection::LEFT || currentDirection == FacingDirection::RIGHT) {
			//Finished moving to the next tile
			if (displacement == mapTileWidth) {
				displacement = 0;
				onMoveEnd(currentDirection);
				currentDirection = nextDirection;
				moving = false;
				if (currentDirection != NONE) {
					changeDirection(currentDirection);
					moving = true;
				}
				walkLeft = !walkLeft;
			}

			//Need to switch the sprite
			else {
				onMove((float)displacement / (float)mapTileWidth);
			}
		}

		//up or down
		else if (currentDirection == FacingDirection::UP || currentDirection == FacingDirection::DOWN) {
			//Finished moving to the next tile
			if (displacement == mapTileHeight) {
				displacement = 0;
				onMoveEnd(currentDirection);
				currentDirection = nextDirection;
				moving = false;
				if (currentDirection != NONE) {
					changeDirection(currentDirection);
					moving = true;
				}
				walkLeft = !walkLeft;
			}

			//Need to switch the sprite
			else {
				onMove((float)displacement / (float)mapTileHeight);
			}
		}
	}
}

void BaseMovementObject::cancelNextMove() { nextDirection = NONE; }

void BaseMovementObject::changeDirection(FacingDirection direction) {
	if (direction == NONE || isMoving()) return;
	currentDirection = direction;
	onChangeDirection(direction);
}

bool BaseMovementObject::isWalkingLeft() const { return walkLeft; }
bool BaseMovementObject::isMoving() const { return moving; }
FacingDirection BaseMovementObject::getCurrentDirection() const { return currentDirection; }
FacingDirection BaseMovementObject::getNextDirection() const { return nextDirection; }
