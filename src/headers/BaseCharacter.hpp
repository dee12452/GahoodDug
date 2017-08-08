#ifndef BASE_CHARACTER_HPP
#define BASE_CHARACTER_HPP

#include "Sprite.hpp"

enum CharacterDirection { CH_UP, CH_DOWN, CH_LEFT, CH_RIGHT };

class BaseCharacter : public Sprite {
public:
	BaseCharacter(const std::string &id, int, int, int, int);
	virtual ~BaseCharacter();

	CharacterDirection getFacingDirection() const;
	bool isMoving() const;

	bool move(const CharacterDirection &, unsigned int);
	void changeFacingDirection(const CharacterDirection &);

protected:
	void onUpdate() override;
	virtual void onMove(const CharacterDirection &, __int64, __int64) = 0;
	virtual void onArrive(const CharacterDirection &, int, int) = 0;
	virtual void onChangeDirection(const CharacterDirection &) = 0;

private:
	static const unsigned int updateTime;
	CharacterDirection currentDirection;
	bool moving;
	__int64 startMove, walkDuration;
	int prevX, prevY;
};

#endif