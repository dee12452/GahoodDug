#include "../headers/BaseCharacter.hpp"
#include "../headers/Util.hpp"
#include "../headers/Constants.hpp"

const unsigned int BaseCharacter::updateTime = 20;
const unsigned int BaseCharacter::defaultMoveTime = 200;

BaseCharacter::BaseCharacter(const std::string &id, int x, int y, int w, int h) 
	: Sprite(id) {
	setSourceRect(x, y, w, h);
	setDestinationRect(0, 0, 0, 0);
	setUpdateTimer(updateTime);
	moving = false;
	currentLayer = 0;
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
	if (moving) return false;
	moving = true;
	changeFacingDirection(direction);
	startMove = Util::getCurrentTimeMillis();
	walkDuration = duration;
	prevX = getX(); prevY = getY();
	onMoveStart(direction);
	return true;
}

void BaseCharacter::onUpdate() {
	if (moving) {
		__int64 nextMove = Util::getCurrentTimeMillis();
		if (nextMove - startMove >= walkDuration) {
			switch (currentDirection) {
			case CH_UP:
				setY(prevY - Constants::TILE_HEIGHT);
				onMoveEnd(CH_UP, prevX, prevY - Constants::TILE_HEIGHT);
				break;
			case CH_DOWN:
				setY(prevY + Constants::TILE_HEIGHT);
				onMoveEnd(CH_DOWN, prevX, prevY + Constants::TILE_HEIGHT);
				break;
			case CH_LEFT:
				setX(prevX - Constants::TILE_WIDTH);
				onMoveEnd(CH_LEFT, prevX - Constants::TILE_WIDTH, prevY);
				break;
			case CH_RIGHT:
				setX(prevX + Constants::TILE_WIDTH);
				onMoveEnd(CH_RIGHT, prevX + Constants::TILE_WIDTH, prevY);
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