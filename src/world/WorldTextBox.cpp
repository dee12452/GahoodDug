#include "WorldTextBox.hpp"

#include "World.hpp"
#include "../game/Game.hpp"
#include "../sprite/Sprites.hpp"
#include "../util/Utils.hpp"

WorldTextBox::WorldTextBox(World *w, SpriteSheet *textBoxSprite, Font *font, bool isDialogue)
	: dialogue(isDialogue), 
	  animIn(false),
	  message(""),
	  world(w), 
	  animTimer(new Timer(Constants::WORLD_MAP_NAME_ANIM_TICK_TIME)),
	  dismissTimer(NULL),
	  messageFont(font) {
	boxSprite = textBoxSprite->createSprite();
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

void WorldTextBox::onTick(Game *) {}
void WorldTextBox::onTickInBackground() {}
void WorldTextBox::setText(const std::string &text) { message = text; }
void WorldTextBox::setFont(Font *font) { messageFont = font; }
void WorldTextBox::show() {}
void WorldTextBox::dismiss() {}
void WorldTextBox::dismissAfter(unsigned int ms) {}
void WorldTextBox::nextLine() {}
void WorldTextBox::drawTextBox(Window *win) {}