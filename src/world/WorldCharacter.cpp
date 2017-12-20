#include "WorldCharacter.hpp"
#include "World.hpp"
#include "../util/Utils.hpp"
#include "../sprite/Sprites.hpp"
#include "../map/Maps.hpp"

WorldCharacter::WorldCharacter(World *world, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed)
    : BaseWorldMover(world, spriteSheet, movementUpdateTime, movementSpeed) {
    changeDirection(FacingDirection::DOWN);
    getSprite()->setDstW(Constants::CHARACTER_WIDTH);
    getSprite()->setDstH(Constants::CHARACTER_HEIGHT);
}

WorldCharacter::~WorldCharacter() {
}

void WorldCharacter::onTickInBackground() {}

void WorldCharacter::onMoveStart(FacingDirection direction) {
    switch(direction) {
        case FacingDirection::LEFT:
            if(getPositionX() == 0 || checkForObstacles(getTileX() - 1, getTileY())) {
                stopNextMovement();
            }
            break;
        case FacingDirection::RIGHT:
            if(getPositionX() == getWorld()->getMap()->getTileWidth() * (getWorld()->getMap()->getWidth() - 1) 
                    || checkForObstacles(getTileX() + 1, getTileY())) {
                stopNextMovement();
            }
            break;
        case FacingDirection::UP:
            if(getPositionY() == 0 || checkForObstacles(getTileX(), getTileY() - 1)) {
                stopNextMovement();
            }
            break;
        case FacingDirection::DOWN:
            if(getPositionY() == getWorld()->getMap()->getTileHeight() * (getWorld()->getMap()->getHeight() - 1) 
                    || checkForObstacles(getTileX(), getTileY() + 1)) {
                stopNextMovement();
            }
            break;
        default:
            break;
    }
}

void WorldCharacter::onMove(float percentToNextTile) {
	if (percentToNextTile < 0.5f) return;

	if (isWalkingLeft()) {
		getSprite()->setSrcX(Constants::CHARACTER_WIDTH);
	}
	else {
		getSprite()->setSrcX(Constants::CHARACTER_WIDTH * 3);
	}
}

void WorldCharacter::onMoveEnd(FacingDirection) {
	getSprite()->setSrcX(0);
}

void WorldCharacter::onChangeDirection(FacingDirection direction) {
	getSprite()->setSrcRect(Util::createRect(0,
		static_cast<int>(direction) * Constants::CHARACTER_HEIGHT,
		Constants::CHARACTER_WIDTH,
		Constants::CHARACTER_HEIGHT));
}

bool WorldCharacter::checkForObstacles(int tileX, int tileY) const {
    //Check for walls in the tiles first
    for(unsigned int i = 0; i < getWorld()->getMap()->getNumberOfLayers(); i++) {
        Tile *tile = getWorld()->getMap()->getTile(i, tileX, tileY);
        if(tile != NULL && 
			tile->getTileType() != Constants::TILE_TYPE_FLOOR && 
			tile->getTileType() != Constants::TILE_TYPE_FLOWER &&
			tile->getTileType() != Constants::TILE_TYPE_GRASS) {
            return true;
        }
    }

    return false;
}
