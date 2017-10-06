#ifndef BASE_WORLD_OBJECT
#define BASE_WORLD_OBJECT

class Sprite;
class SpriteSheet;
class Game;
class Window;

class BaseWorldObject {
public:
    BaseWorldObject(SpriteSheet *spriteSheet);
    virtual ~BaseWorldObject();

    virtual void update(Game *game) = 0;
    virtual void draw(Window *window);

    void setPositionX(int x);
    void setPositionY(int y);
    void setLayer(int newLayer);

    int getPositionX() const;
    int getPositionY() const;
    int getLayer() const;
    Sprite * getSprite() const;

private:
    int posX, posY, layer;
    Sprite *objectSprite;
};

#endif 
