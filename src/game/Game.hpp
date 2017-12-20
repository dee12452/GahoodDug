#ifndef GAHOODMON_HPP
#define GAHOODMON_HPP

#include <vector>
#include <map>
#include <string>
#include "Window.hpp"

struct SDL_Thread;
class Timer;
class SpriteSheet;
class BaseScreen;
class Font;
class BaseGameObject;

class Game {
public:
    Game();
    ~Game();

    /* NEVER CALL THESE FUNCTIONS */
    void run();
    void runInBackground();
    void loadSpriteSheet(const char *path);
    /* ************************** */

    //Tells if the game is running or not
    bool isRunning() const;

    //Quit the game, begins the cleanup process before shutting down
    void quit();

    //Request a screen change
    void requestNewScreen(BaseScreen *newScreen);

    //Add a game object to the game to be ticked
	static void registerObjectTick(BaseGameObject *obj);

    //Remove a game object from the object tick list
	static void unregisterObjectTick(BaseGameObject *obj);

    //Get the game window
    Window * getWindow() const;

    //Get a sprite sheet to make a sprite
    SpriteSheet * getSpriteSheet(const char *spriteSheetName) const;
    
    //Get a font to make a text sprite
    Font * getFont(const char *fontName) const;

private:
    //Member variables//
    bool running;
    Window *window;
    Timer *fpsTimer, *tickTimer;
    SDL_Thread *backgroundThread;
    BaseScreen *currentScreen, *nextScreen;

    //Member functions//
    void init();
    void update();
    void deinit();
    void changeScreens();

	static std::vector<BaseGameObject *> updatables;
    std::map<std::string, SpriteSheet *> spriteSheets;
    std::map<std::string, Font *> fonts;
};

#endif
