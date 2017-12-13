#ifndef BASE_WORLD_OBJECT
#define BASE_WORLD_OBJECT

#include "../game/BaseGameObject.hpp"

class Sprite;
class SpriteSheet;
class Game;
class Window;
class World;

class BaseWorldObject : public BaseGameObject {
public:
    BaseWorldObject(SpriteSheet *spriteSheet);
    virtual ~BaseWorldObject();

    void setPositionX(int x);
    void setPositionY(int y);
    void setLayer(int newLayer);

	int getTileX(World *world) const;
	int getTileY(World *world) const;
    int getPositionX() const;
    int getPositionY() const;
    int getLayer() const;
    Sprite * getSprite() const;

private:
    int posX, posY, layer;
    Sprite *objectSprite;
};

#endif 
