#include "../headers/BaseCharacter.hpp"

#include <SDL2/SDL_rect.h>
#include "../headers/Util.hpp"
#include "../headers/Constants.hpp"

const int64_t BaseCharacter::updateTime = 25;
const int64_t BaseCharacter::defaultMoveTime = 325;

BaseCharacter::BaseCharacter(const std::string &id)
	: BaseCharacter(id,
		0,
		0,
		Constants::SPRITE_CHARACTER_WIDTH,
		Constants::SPRITE_CHARACTER_HEIGHT) {
}

BaseCharacter::BaseCharacter(const std::string &id, int x, int y, int w, int h) 
	: Sprite(id) {
	setSourceRect(x, y, w, h);
	setDestinationRect(0, 0, Constants::SPRITE_CHARACTER_WIDTH, Constants::SPRITE_CHARACTER_HEIGHT);
	setUpdateTimer(updateTime);
	moving = false;
	walkLeft = false;
	currentLayer = 0;
	currentDirection = CH_NONE;
	nextDirection = CH_NONE;
}

BaseCharacter::BaseCharacter(const std::string &id, int x, int y, int w, int h, int dx, int dy, int dw, int dh) 
	: BaseCharacter(id, x, y, w, h) {
	setDestinationRect(dx, dy, dw, dh);
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
	if (moving || direction == CH_NONE) {
		nextDirection = direction;
		return false;
	}
	walkLeft = !walkLeft;
	moving = true;
	changeFacingDirection(direction);
	startMove = Util::getCurrentTimeMillis();
	walkDuration = duration;
	prevX = getX(); prevY = getY();
	onMoveStart(direction);
	return true;
}

void BaseCharacter::cancelNextMove() { nextDirection = CH_NONE;  }

void BaseCharacter::onUpdate() {
	if (moving) {
		int64_t nextMove = Util::getCurrentTimeMillis();
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
            default:
                break;
			}
			startMove = 0;
			walkDuration = 0;
			moving = false;
			if (nextDirection != CH_NONE) {
				move(nextDirection);
			}
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
            default:
                break;
			}
		}
	}
}

void BaseCharacter::onMove(const CharacterDirection &dir, int64_t curr, int64_t total) {
	float percentage = static_cast<float>(curr) / static_cast<float>(total) * 100;
	SDL_Rect chSrc = *(getSourceRect());
	if (percentage <= 45) {
		if(walkLeft)
			chSrc.x = chSrc.w * 1;
		else
			chSrc.x = chSrc.w * 3;
	}
	else if (percentage <= 80) {
		chSrc.x = chSrc.w * 2;
	}
	setSourceRect(chSrc);
}

void BaseCharacter::onMoveEnd(const CharacterDirection &, int, int) {
	SDL_Rect chSrc = *(getSourceRect());
	chSrc.x = 0;
	setSourceRect(chSrc);
}

void BaseCharacter::onMoveStart(const CharacterDirection &dir) {
	SDL_Rect chSrc = *(getSourceRect());
	switch (dir) {
	case CH_UP:
		chSrc.y = chSrc.h * Constants::SPRITE_CHARACTER_FACE_UP;
		break;
	case CH_DOWN:
		chSrc.y = chSrc.h * Constants::SPRITE_CHARACTER_FACE_DOWN;
		break;
	case CH_LEFT:
		chSrc.y = chSrc.h * Constants::SPRITE_CHARACTER_FACE_LEFT;
		break;
	case CH_RIGHT:
		chSrc.y = chSrc.h * Constants::SPRITE_CHARACTER_FACE_RIGHT;
		break;
    default:
        break;
	}
	setSourceRect(chSrc);
}

void BaseCharacter::onChangeDirection(const CharacterDirection &) {}
