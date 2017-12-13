#ifndef BASE_MOVEMENT_OBJECT
#define BASE_MOVEMENT_OBJECT

#include "BaseWorldObject.hpp"

class Timer;

typedef enum FacingDirection { NONE = 4, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 0 } FacingDirection;

class BaseMovementObject : public BaseWorldObject {
public:
	BaseMovementObject(SpriteSheet *spriteSheet, 
		int tileW, int tileH, 
		int movementUpdateTime, int movementSpeed);
	~BaseMovementObject() override;

	void move(FacingDirection direction);
	void changeDirection(FacingDirection direction);
	void cancelNextMove();

	bool isMoving() const;
	FacingDirection getCurrentDirection() const;
	FacingDirection getNextDirection() const;

protected:
	void onTick(Game *game) override;

	virtual void onMoveStart();
	virtual void onMove();
	virtual void onMoveEnd();
	virtual void onChangeDirection(FacingDirection direction);

private:
	int displacement, moveSpeed;
	FacingDirection currentDirection, nextDirection;
	Timer *movementTimer;
	bool moving, walkLeft;
};

#endif