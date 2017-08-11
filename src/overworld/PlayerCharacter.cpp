#include "../headers/PlayerCharacter.hpp"

#include "../headers/Constants.hpp"

PlayerCharacter::PlayerCharacter(const std::string &id, int x, int y, int w, int h) 
	: BaseCharacter(id, x, y, w, h) {
}

PlayerCharacter::~PlayerCharacter() {}

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