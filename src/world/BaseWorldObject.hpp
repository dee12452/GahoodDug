#ifndef BASE_WORLD_OBJECT
#define BASE_WORLD_OBJECT

#include "../game/BaseGameObject.hpp"

class Sprite;
class SpriteSheet;
class Game;
class Window;
class Map;

class BaseWorldObject : public BaseGameObject {
public:
    BaseWorldObject(Map *map, SpriteSheet *spriteSheet);
    virtual ~BaseWorldObject();

	void setTileX(int x);
	void setTileY(int y);
    void setPositionX(int x);
    void setPositionY(int y);
    void setLayer(int newLayer);

	int getTileX() const;
	int getTileY() const;
    int getPositionX() const;
    int getPositionY() const;
    int getLayer() const;
    Sprite *getSprite() const;

protected:
    Map *map;

private:
    int tileX, tileY, posX, posY, layer;
    Sprite *objectSprite;
};

#endif 
