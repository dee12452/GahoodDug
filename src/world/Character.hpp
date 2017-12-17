#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "BaseMovementObject.hpp"

class Timer;

class Character : public BaseMovementObject {
public:
    Character(Map *map, SpriteSheet *sheet, int movementUpdateTime, int movementSpeed);
    ~Character() override;

protected:
	void onTickInBackground() override;
	void onMoveStart(FacingDirection direction) override;
	void onMove(float percentToNextTile) override;
	void onMoveEnd(FacingDirection direction) override;
	void onChangeDirection(FacingDirection direction) override;
};

#endif
