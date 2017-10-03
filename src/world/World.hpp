#ifndef WORLD_HPP
#define WORLD_HPP

class Map;
class Window;

class World {
public:
    World(Map *firstMap);
    ~World();

    void update();
    void draw(Window *win);

private:
    Map *currentMap;
};

#endif
