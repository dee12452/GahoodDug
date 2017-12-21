#ifndef WORLD_TEXT_BOX_HPP
#define WORLD_TEXT_BOX_HPP

#include "../game/BaseGameObject.hpp"
#include <string>

class Game;
class Window;
class World;
class Timer;
class SpriteSheet;
class Sprite;
class FontSprite;
class Font;

class WorldTextBox : public BaseGameObject {
public:
	WorldTextBox(World *w, const char *windowSkinImageFile, const char *fontFile, bool isDialogue);
	~WorldTextBox() override;

	void show();
	void dismiss();
	void dismissAfter(unsigned int ms);
	void nextLine();
	void drawTextBox(Window *win);
	void setFont(Font *font);
	void setText(const std::string &text);

protected:
	void onTick(Game *game) override;
	void onTickInBackground() override;

private:
	bool dialogue, animIn;
	std::string message;
	World *world;
	Timer *animTimer;
	Timer *dismissTimer;
	Sprite *boxSprite;
	Font *messageFont;
	FontSprite *messageSprite;
};

#endif