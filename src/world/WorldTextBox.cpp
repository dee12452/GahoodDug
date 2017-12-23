#include "WorldTextBox.hpp"

#include "World.hpp"
#include "../game/Game.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"

WorldTextBox::WorldTextBox(World *w, SpriteSheet *image, Font *font, bool isDialogue) : 
	  BaseWorldObject(w, image, Constants::WORLD_MAP_NAME_ANIM_TICK_TIME),
	  dialogue(isDialogue), 
	  animIn(false),
	  changedText(false),
	  changedFont(false),
	  drawBox(false),
	  message(""),
	  dismissTimer(NULL) {
	int width, height;
	getImageDimensions(width, height);
	setSourceRect(Util::createRect(0, 0, width, height));
	setDestinationRect(Util::createRect(0, -height, width, height));
}

WorldTextBox::~WorldTextBox() { 
	messageFont = NULL;
	if (dismissTimer != NULL) {
		delete dismissTimer;
		dismissTimer = NULL;
	}
	if (messageSprite != NULL) {
		delete messageSprite;
		messageSprite = NULL;
	}
}

void WorldTextBox::onObjectTick(Game *) {
	if (dismissTimer != NULL && dismissTimer->check()) {
		dismiss();
	}
	else if(drawBox) {
		if (getRawY() < 0) {
			setRawY(getRawY() + 4);
		}
	}
}

void WorldTextBox::onTickInBackground() {}

void WorldTextBox::setText(const std::string &text) { message = text; changedText = true; }

void WorldTextBox::setFont(Font *font) { messageFont = font; changedFont = true; }

void WorldTextBox::show() {
	if (drawBox) return;
	drawBox = true;
}

void WorldTextBox::dismiss() {
	if (!drawBox) return;
	drawBox = false;
	setRawY(-getHeight());
}

void WorldTextBox::dismissAfter(unsigned int ms) {
	if (dismissTimer != NULL) delete dismissTimer;
	dismissTimer = new Timer(ms);
}

void WorldTextBox::nextLine() {}

void WorldTextBox::onDraw(Window *win) {
	if (changedText) {
		//TODO: change the text
		changedText = false;
	}
	if (changedFont) {
		//TODO: change the font
		changedFont = false;
	}
	if (drawBox) {
		//TODO: draw the box
		if (dialogue) {

		}
		else {
			BaseWorldObject::onDraw(win);
		}
	}
}