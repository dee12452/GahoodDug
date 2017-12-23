#ifndef BASE_WORLD_OBJECT
#define BASE_WORLD_OBJECT

#include "../game/BaseGameObject.hpp"

class Sprite;
class SpriteSheet;
class Game;
class Window;
class World;
struct SDL_Rect;

class BaseWorldObject : public BaseGameObject {
public:
    BaseWorldObject(World *world, SpriteSheet *image, int tickTime);
    virtual ~BaseWorldObject();

    World * getWorld() const;
	
	void setRawX(int x) const;
	void setRawY(int y) const;
	void setWidth(int w) const;
	void setHeight(int h) const;
    void setTileX(int x);
	void setTileY(int y);
    void setPositionX(int x);
    void setPositionY(int y);
    void setLayer(int newLayer);

	int getRawX() const;
	int getRawY() const;
	int getWidth() const;
	int getHeight() const;
	int getTileX() const;
	int getTileY() const;
    int getPositionX() const;
    int getPositionY() const;
    int getLayer() const;
    
	void setSourceRect(const SDL_Rect &srcRect) const;
	void setDestinationRect(const SDL_Rect &dstRect) const;
	SDL_Rect getSourceRect() const;
	SDL_Rect getDestinationRect() const;

	void getImageDimensions(int &w, int &h) const;

protected:
	virtual void onDraw(Window *win);

private:
    World *world;
    int tileX, tileY, posX, posY, layer;
    Sprite *objectSprite;
};

#endif 
