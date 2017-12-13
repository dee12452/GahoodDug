#include "Character.hpp"
#include "../util/Utils.hpp"
#include "../sprite/Sprites.hpp"

Character::Character(SpriteSheet *spriteSheet) 
    : BaseWorldObject(spriteSheet),
    displacement(0),
    nextDirection(NONE), 
    movementTimer(new Timer(Constants::CHARACTER_WALK_TIMER)), 
    moving(false),
    walkLeft(true) {
    changeDirection(DOWN);
    getSprite()->setDstW(Constants::CHARACTER_WIDTH);
    getSprite()->setDstH(Constants::CHARACTER_HEIGHT);
}

Character::~Character() {
    if(movementTimer != NULL) {
        delete movementTimer;
        movementTimer = NULL;
    }
}

void Character::onTickInBackground() {}

void Character::onTick(Game *) {
    if(moving && currentDirection != NONE && movementTimer->check()) {
        switch(currentDirection) {
            case UP:
                setPositionY(getPositionY() - Constants::CHARACTER_WALK_SPEED);
                break;
            case DOWN:
                setPositionY(getPositionY() + Constants::CHARACTER_WALK_SPEED);
                break;
            case LEFT:
                setPositionX(getPositionX() - Constants::CHARACTER_WALK_SPEED);
                break;
            case RIGHT:
                setPositionX(getPositionX() + Constants::CHARACTER_WALK_SPEED);
                break;
            default:
                break;
        }
        displacement += Constants::CHARACTER_WALK_SPEED;
        
        //Finished moving to the next tile
        if(displacement == tileWidth) {
            displacement = 0;
            currentDirection = nextDirection;
            getSprite()->setSrcX(0);
            moving = false;
            if(currentDirection != NONE) {
                changeDirection(currentDirection);
                moving = true;
            }
            walkLeft = !walkLeft;
        }

        //Need to switch the sprite
        else if(displacement == tileWidth / 2) {
            if(walkLeft) {
                getSprite()->setSrcX(Constants::CHARACTER_WIDTH);
            }
            else {
                getSprite()->setSrcX(Constants::CHARACTER_WIDTH * 3);
            }
        }
    }
}

bool Character::isMoving() const { return moving; }

FacingDirection Character::getCurrentDirection() const { return currentDirection; }
FacingDirection Character::getNextDirection() const { return nextDirection; }

void Character::move(FacingDirection direction) {
    if(moving) {
        nextDirection = direction;
    }
    else {
        changeDirection(direction);
        moving = true;
    }
}

void Character::cancelNextMove() { nextDirection = NONE; }

void Character::changeDirection(FacingDirection direction) {
    if(direction == NONE || isMoving()) return;
    currentDirection = direction;
    getSprite()->setSrcRect(Util::createRect(0, 
                static_cast<int>(direction) * Constants::CHARACTER_HEIGHT,
                Constants::CHARACTER_WIDTH,
                Constants::CHARACTER_HEIGHT));
}
