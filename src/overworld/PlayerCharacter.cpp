#include "../headers/PlayerCharacter.hpp"

#include "../headers/Constants.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_log.h>

PlayerCharacter::PlayerCharacter(const std::string &id, int x, int y, int w, int h) 
	: BaseCharacter(id, x, y, w, h) {
	getDestinationRect()->x = Constants::WINDOW_WIDTH / 2 - getDestinationRect()->w / 2;
	getDestinationRect()->y = Constants::WINDOW_HEIGHT / 2 - getDestinationRect()->h / 2;
}

PlayerCharacter::~PlayerCharacter() {
	SDL_Log("%d, %d\n", getDestinationRect()->x, getDestinationRect()->y);
}

std::string PlayerCharacter::getObjectType() {
	return Constants::OBJECT_TYPE_PLAYER;
}

void PlayerCharacter::onMove(const CharacterDirection &dir, __int64 curr, __int64 total) {
	BaseCharacter::onMove(dir, curr, total);
}

void PlayerCharacter::onMoveEnd(const CharacterDirection &dir, int x, int y) {
	BaseCharacter::onMoveEnd(dir, x, y);
}

void PlayerCharacter::onMoveStart(const CharacterDirection &dir) {
	BaseCharacter::onMoveStart(dir);
}

void PlayerCharacter::onChangeDirection(const CharacterDirection &) {
}