#ifndef WORLD_HPP
#define WORLD_HPP

class Game;
class Map;
class Window;
class Sprite;
class Character;

class World {
public:
    World(Game *game);
    ~World();

    void drawWorld(Window *win);
    Character * getPlayer() const;

private:
    Map *currentMap;
    Sprite *tilesetSprite;
    Character *player;
};

#endif
