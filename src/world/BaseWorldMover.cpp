#include "BaseWorldMover.hpp"
#include "World.hpp"
#include "../map/Map.hpp"
#include "../util/Timer.hpp"
#include "../sprite/Sprite.hpp"
#include "../util/Utils.hpp"

BaseWorldMover::BaseWorldMover(World *world, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed) 
	: BaseWorldObject(world, spriteSheet),
	displacement(0),
	moveSpeed(movementSpeed),
	nextMoveSpeed(movementSpeed),
	nextDirection(NONE),
	movementTimer(new Timer(movementUpdateTime)),
	moving(false),
    canMove(true),
	walkLeft(true) {}

BaseWorldMover::~BaseWorldMover() {
	if (movementTimer != NULL) {
		delete movementTimer;
		movementTimer = NULL;
	}
}

void BaseWorldMover::move(FacingDirection direction) {
	if (moving) {
		nextDirection = direction;
	}
	else {
		changeDirection(direction);
		moving = true;
	}
}

void BaseWorldMover::onTick(Game *) {
	if (moving && currentDirection != FacingDirection::NONE && movementTimer->check()) {
        if(displacement == 0) { onMoveStart(currentDirection); } 
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
			if (displacement == getWorld()->getMap()->getTileWidth()) {
				displacement = 0;
				if(nextMoveSpeed != moveSpeed) moveSpeed = nextMoveSpeed;
                onMoveEnd(currentDirection);
				currentDirection = nextDirection;
				moving = false;
                canMove = true;
				if (currentDirection != NONE) {
					changeDirection(currentDirection);
					moving = true;
				}
				walkLeft = !walkLeft;
			}

			//Need to switch the sprite
			else {
				onMove((float)displacement / (float)getWorld()->getMap()->getTileWidth());
			}
		}

		//up or down
		else if (currentDirection == FacingDirection::UP || currentDirection == FacingDirection::DOWN) {
			//Finished moving to the next tile
			if (displacement == getWorld()->getMap()->getTileHeight()) {
				displacement = 0;
				if(nextMoveSpeed != moveSpeed) moveSpeed = nextMoveSpeed;
				onMoveEnd(currentDirection);
				currentDirection = nextDirection;
				moving = false;
                canMove = true;
				if (currentDirection != NONE) {
					changeDirection(currentDirection);
					moving = true;
				}
				walkLeft = !walkLeft;
			}

			//Need to switch the sprite
			else {
				onMove((float)displacement / (float)getWorld()->getMap()->getTileHeight());
			}
		}
	}
}

void BaseWorldMover::cancelNextMove() { nextDirection = NONE; }

void BaseWorldMover::changeDirection(FacingDirection direction) {
	if (direction == NONE || isMoving()) return;
	currentDirection = direction;
	onChangeDirection(direction);
}

int BaseWorldMover::getMoveSpeed() const { return moveSpeed; }
void BaseWorldMover::setMoveSpeed(int speed) { if(moving) nextMoveSpeed = speed; else moveSpeed = speed; }
bool BaseWorldMover::isWalkingLeft() const { return walkLeft; }
bool BaseWorldMover::isMoving() const { return moving; }
void BaseWorldMover::stopNextMovement() { canMove = false; }
FacingDirection BaseWorldMover::getCurrentDirection() const { return currentDirection; }
FacingDirection BaseWorldMover::getNextDirection() const { return nextDirection; }
