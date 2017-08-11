#ifndef BASE_GAME_OBJECT
#define BASE_GAME_OBJECT

#include "Sprite.hpp"

class BaseGameObject : public Sprite {
public:
	BaseGameObject(const std::string &id);
	BaseGameObject(const std::string &id, int, int, int, int, int, int, int, int);
	BaseGameObject(const std::string &id, const SDL_Rect &, const SDL_Rect &);
	virtual ~BaseGameObject() override;

	virtual std::string getObjectType() = 0;
};

#endif