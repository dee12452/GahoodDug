#ifndef BASE_MOVEMENT_OBJECT
#define BASE_MOVEMENT_OBJECT

#include "BaseWorldObject.hpp"

class Timer;

typedef enum FacingDirection { NONE = 4, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 0 } FacingDirection;

class BaseMovementObject : public BaseWorldObject {
public:
	BaseMovementObject(Map *map, SpriteSheet *spriteSheet, int movementUpdateTime, int movementSpeed);
	virtual ~BaseMovementObject() override;

	void move(FacingDirection direction);
	void changeDirection(FacingDirection direction);
	void cancelNextMove();

	bool isMoving() const;
	FacingDirection getCurrentDirection() const;
	FacingDirection getNextDirection() const;

protected:

	bool isWalkingLeft() const;
	void onTick(Game *game) override;

	virtual void onMove(float percentToNextTile) = 0;
	virtual void onMoveEnd(FacingDirection direction) = 0;
	virtual void onChangeDirection(FacingDirection direction) = 0;

private:
	int displacement, moveSpeed;
	FacingDirection currentDirection, nextDirection;
	Timer *movementTimer;
	bool moving, canMove, walkLeft;
};

#endif
