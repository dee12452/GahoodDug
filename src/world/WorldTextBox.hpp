#ifndef WORLD_TEXT_BOX_HPP
#define WORLD_TEXT_BOX_HPP

#include "BaseWorldObject.hpp"
#include <string>

class SpriteSheet;
class Sprite;
class FontSprite;
class Font;

class WorldTextBox : public BaseWorldObject {
public:
	WorldTextBox(World *w, SpriteSheet *image, Font *fontFile, bool isDialogue);
	~WorldTextBox() override;

	void show();
	void dismiss();
	void dismissAfter(unsigned int ms);
	void nextLine();
	void setFont(Font *font);
	void setText(const std::string &text);

protected:
	void onObjectTick(Game *game) override;
	void onTickInBackground() override;
	void onDraw(Window *win) override;

private:
	bool dialogue, animIn, changedText, changedFont, drawBox;
	std::string message;
	Timer *dismissTimer;
	Font *messageFont;
	FontSprite *messageSprite;
};

#endif