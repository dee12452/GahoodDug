#ifndef WORLD_HPP
#define WORLD_HPP

class Game;
class Map;
class Window;
class Sprite;
class WorldCharacter;
struct SDL_Texture;

class World {
public:
    World(Game *game);
    ~World();

    void drawWorld(Window *win);

    WorldCharacter * getPlayer() const;
    Map * getMap() const;
	int getTileWidth() const;
	int getTileHeight() const;

    void changeMap(Game *game, const char * const mapFile);

private:
    Map *map;
    SDL_Texture *mapTexture;
    WorldCharacter *player;
};

#endif
