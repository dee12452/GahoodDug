#include "WorldTextBox.hpp"

#include "World.hpp"
#include "../game/Game.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"

WorldTextBox::WorldTextBox(World *w, const char *windowSkinImageFile, const char *fontFile, bool isDialogue)
	: dialogue(isDialogue), 
	  animIn(false),
	  changedText(false),
	  changedFont(false),
	  drawBox(false),
	  message(""),
	  world(w), 
	  animTimer(new Timer(Constants::WORLD_MAP_NAME_ANIM_TICK_TIME)),
	  dismissTimer(NULL),
	  messageFont(Game::getFont(fontFile)) {
	boxSprite = Game::getSpriteSheet(windowSkinImageFile)->createSprite();
	int width, height;
	Util::querySpriteSourceImage(boxSprite, width, height);
	boxSprite->setSrcRect(Util::createRect(0, 0, width, height));
	boxSprite->setDstRect(Util::createRect(0, 0, width, height));
}

WorldTextBox::~WorldTextBox() { 
	world = NULL; 
	messageFont = NULL;
	if (dismissTimer != NULL) {
		delete dismissTimer;
		dismissTimer = NULL;
	}
	if (animTimer != NULL) {
		delete animTimer;
		animTimer = NULL;
	}
	if (boxSprite != NULL) {
		delete boxSprite;
		boxSprite = NULL;
	}
	if (messageSprite != NULL) {
		delete messageSprite;
		messageSprite = NULL;
	}
}

void WorldTextBox::onTick(Game *) {
	if (dismissTimer != NULL && dismissTimer->check()) {
		dismiss();
	}
	else if(drawBox) {
		if (boxSprite->getDstY() < boxSprite->getDstH()) {
			boxSprite->setDstY(boxSprite->getDstY() + 1);
		}
	}
}

void WorldTextBox::onTickInBackground() {}

void WorldTextBox::setText(const std::string &text) { message = text; changedText = true; }

void WorldTextBox::setFont(Font *font) { messageFont = font; changedFont = true; }

void WorldTextBox::show() {
	if (drawBox) return;
	Game::registerObjectTick(this);
	drawBox = true;
}

void WorldTextBox::dismiss() {
	if (!drawBox) return;
	Game::unregisterObjectTick(this);
	drawBox = false;
	boxSprite->setDstY(0);
}

void WorldTextBox::dismissAfter(unsigned int ms) {
	if (dismissTimer != NULL) delete dismissTimer;
	dismissTimer = new Timer(ms);
}

void WorldTextBox::nextLine() {}

void WorldTextBox::drawTextBox(Window *win) {
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
			boxSprite->draw(win);
		}
	}
}