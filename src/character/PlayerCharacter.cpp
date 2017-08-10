#include "../headers/PlayerCharacter.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_log.h>
#include "../headers/Constants.hpp"

PlayerCharacter::PlayerCharacter(const std::string &id, int x, int y, int w, int h) 
	: BaseCharacter(id, x, y, w, h) {
}

PlayerCharacter::PlayerCharacter(const std::string &id, 
	int sX, 
	int sY, 
	int sW, 
	int sH,
	int dX,
	int dY,
	int dW,
	int dH)
	: BaseCharacter(id, sX, sY, sW, sH) {
	setDestinationRect(dX, dY, dW, dH);
}

PlayerCharacter::~PlayerCharacter() {}

void PlayerCharacter::onMove(const CharacterDirection &dir, __int64 curr, __int64 total) {
	float percentage = static_cast<float>(curr) / static_cast<float>(total) * 100;
	SDL_Rect chSrc = *(getSourceRect());
	if (percentage <= 25) {
		chSrc.x = chSrc.w * 1;
	}
	else if (percentage <= 50) {
		chSrc.x = chSrc.w * 2;
	}
	else if (percentage <= 75) {
		chSrc.x = chSrc.w * 3;
	}
	setSourceRect(chSrc);
}

void PlayerCharacter::onMoveEnd(const CharacterDirection &, int, int) {
	SDL_Rect chSrc = *(getSourceRect());
	chSrc.x = 0;
	setSourceRect(chSrc);
}

void PlayerCharacter::onMoveStart(const CharacterDirection &dir) {
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
	}
	setSourceRect(chSrc);
}

void PlayerCharacter::onChangeDirection(const CharacterDirection &) {

}