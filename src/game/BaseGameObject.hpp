#ifndef BASE_GAME_OBJ
#define BASE_GAME_OBJ

class Game;
class Window;
class Timer;

class BaseGameObject {
public:
	BaseGameObject();
	BaseGameObject(unsigned int tickTime);
	virtual ~BaseGameObject();

	void tick(Game *game);
	void draw(Window *win);
	void tickInBackground();

protected:
	virtual void onGameTick(Game *game) {}
	virtual void onObjectTick(Game *game) {}
	virtual void onDraw(Window *win) {}
	virtual void onTickInBackground() {}

private:
	Timer *tickTimer;
};

#endif