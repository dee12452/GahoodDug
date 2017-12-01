#ifndef BASE_GAME_OBJ
#define BASE_GAME_OBJ

class Game;

class BaseGameObject {
public:
	BaseGameObject();
	~BaseGameObject();

	void tick(Game *game);
	void tickInBackground();

protected:
	virtual void onTick(Game *game) = 0;
	virtual void onTickInBackground() = 0;
};

#endif