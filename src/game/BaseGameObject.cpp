#include "BaseGameObject.hpp"

#include "../util/Timer.hpp"

BaseGameObject::BaseGameObject()
	: tickTimer(NULL) {}

BaseGameObject::BaseGameObject(unsigned int tickTime) 
	: tickTimer(new Timer(tickTime)) {}

BaseGameObject::~BaseGameObject() {
	if (tickTimer != NULL) {
		delete tickTimer;
		tickTimer = NULL;
	}
}

void BaseGameObject::tick(Game *game) {
	if (tickTimer != NULL && tickTimer->check()) { onObjectTick(game); }
	onGameTick(game);
}

void BaseGameObject::tickInBackground() { onTickInBackground(); }

void BaseGameObject::draw(Window *win) { onDraw(win); }