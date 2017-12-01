#include "BaseGameObject.hpp"

BaseGameObject::BaseGameObject() {}

BaseGameObject::~BaseGameObject() {}

void BaseGameObject::tick(Game *game) { onTick(game); }

void BaseGameObject::tickInBackground() { onTickInBackground(); }