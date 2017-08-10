#ifndef BASE_CHARACTER_HPP
#define BASE_CHARACTER_HPP

#include "Sprite.hpp"

enum CharacterDirection { CH_UP, CH_DOWN, CH_LEFT, CH_RIGHT };

class BaseCharacter : public Sprite {
public:
	BaseCharacter(const std::string &id, int, int, int, int);
	virtual ~BaseCharacter() override;

	CharacterDirection getFacingDirection() const;
	bool isMoving() const;

	bool move(const CharacterDirection &);
	bool move(const CharacterDirection &, unsigned int);
	void changeFacingDirection(const CharacterDirection &);
	uint8_t getCurrentMapLayer() const;
	void setCurrentMapLayer(uint8_t);

protected:
	void onUpdate() override;
	virtual void onMoveStart(const CharacterDirection &) = 0;
	virtual void onMove(const CharacterDirection &, __int64, __int64) = 0;
	virtual void onMoveEnd(const CharacterDirection &, int, int) = 0;
	virtual void onChangeDirection(const CharacterDirection &) = 0;

private:
	static const unsigned int updateTime, defaultMoveTime;
	CharacterDirection currentDirection;
	bool moving;
	__int64 startMove, walkDuration;
	int prevX, prevY;
	uint8_t currentLayer;
};

#endif