#include "../headers/BaseCharacter.hpp"
#include "../headers/Util.hpp"
#include "../headers/Constants.hpp"

const unsigned int BaseCharacter::updateTime = 100;

BaseCharacter::BaseCharacter(const std::string &id, int x, int y, int w, int h) 
	: Sprite(id) {
	setSourceRect(x, y, w, h);
	setUpdateTimer(updateTime);
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

bool BaseCharacter::move(const CharacterDirection &direction, unsigned int duration) {
	if (moving) return false;
	moving = true;
	changeFacingDirection(direction);
	startMove = Util::getCurrentTimeMillis();
	walkDuration = duration;
	prevX = getX(); prevY = getY();
	return true;
}

void BaseCharacter::onUpdate() {
	if (moving) {
		__int64 nextMove = Util::getCurrentTimeMillis();
		if (nextMove - startMove >= walkDuration) {
			switch (currentDirection) {
			case CH_UP:
				setY(prevY - Constants::TILE_HEIGHT);
				onArrive(CH_UP, prevX, prevY - Constants::TILE_HEIGHT);
				break;
			case CH_DOWN:
				setY(prevY + Constants::TILE_HEIGHT);
				onArrive(CH_DOWN, prevX, prevY + Constants::TILE_HEIGHT);
				break;
			case CH_LEFT:
				setX(prevX - Constants::TILE_WIDTH);
				onArrive(CH_LEFT, prevX - Constants::TILE_WIDTH, prevY);
				break;
			case CH_RIGHT:
				setX(prevX + Constants::TILE_WIDTH);
				onArrive(CH_RIGHT, prevX + Constants::TILE_WIDTH, prevY);
				break;
			}
			startMove = 0;
			walkDuration = 0;
			moving = false;
		}
		else {
			float percentage = static_cast<float>(nextMove - startMove) / static_cast<float> (walkDuration);
			switch (currentDirection) {
			case CH_UP:
				setY(prevY - static_cast<int>(Constants::TILE_HEIGHT * percentage));
				onMove(CH_UP, nextMove - startMove, walkDuration);
				break;
			case CH_DOWN:
				setY(prevY + static_cast<int>(Constants::TILE_HEIGHT * percentage));
				onMove(CH_DOWN, nextMove - startMove, walkDuration);
				break;
			case CH_LEFT:
				setX(prevX - static_cast<int>(Constants::TILE_WIDTH * percentage));
				onMove(CH_LEFT, nextMove - startMove, walkDuration);
				break;
			case CH_RIGHT:
				setX(prevX + static_cast<int>(Constants::TILE_WIDTH * percentage));
				onMove(CH_RIGHT, nextMove - startMove, walkDuration);
				break;
			}
		}
	}
}