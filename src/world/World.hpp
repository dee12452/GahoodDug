#ifndef WORLD_HPP
#define WORLD_HPP

class Game;
class Map;
class Window;
class Sprite;
class Character;
struct SDL_Texture;

class World {
public:
    World(Game *game);
    ~World();

    void drawWorld(Window *win);

    Character * getPlayer() const;
	int getTileWidth() const;
	int getTileHeight() const;

    void changeMap(Game *game, const char * const mapFile);

private:
    Map *currentMap;
    SDL_Texture *mapTexture;
    Character *player;
};

#endif
