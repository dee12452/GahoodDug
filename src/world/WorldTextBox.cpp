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
	  changedFont(true),
	  drawBox(false),
	  message(""),
	  dismissTimer(NULL),
	  messageFont(font),
	  messageSprite(NULL) {
	int width, height;
	getImageDimensions(width, height);
	setSourceRect(Util::createRect(0, 0, width, height));
	setDestinationRect(Util::createRect(0, -height, width * 5, height * 2));
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
	else if(drawBox && animIn) {
		if (getRawY() < 0) {
			setRawY(getRawY() + 4);
			if (messageSprite != NULL) {
				SDL_Rect textRect = Util::createRect(getRawX() + getWidth() / 4,
					getRawY() + getHeight() / 4,
					getWidth() / 2, 
					getHeight() / 2);
				messageSprite->getSprite()->setDstRect(textRect);
			}
		}
		else {
			animIn = false;
		}
	}
}

void WorldTextBox::onTickInBackground() {}

void WorldTextBox::setText(const std::string &text) { message = text; changedText = true; }

void WorldTextBox::setFont(Font *font) { messageFont = font; changedFont = true; }

void WorldTextBox::show() {
	if (drawBox) return;
	drawBox = true;
	if (!dialogue) animIn = true;
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
		if (messageSprite != NULL) messageSprite->setText(win, message);
		changedText = false;
	}
	if (changedFont) {
		if (messageSprite != NULL) delete messageSprite;
		messageSprite = messageFont->createFontSprite(win, message);
		changedFont = false;
	}
	if (drawBox) {
		//TODO: draw the box
		if (dialogue) {

		}
		else {
			BaseWorldObject::onDraw(win);
			messageSprite->draw(win);
		}
	}
}