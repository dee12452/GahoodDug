#ifndef LAUNCH_SCREEN_HPP
#define LAUNCH_SCREEN_HPP

#include "BaseScreen.hpp"
#include <string>

class FontSprite;

class LaunchScreen : public BaseScreen {
public:
    LaunchScreen(Game *game);
    ~LaunchScreen() override;

protected:
    void onDraw(Window *win) override;
    void onUpdate(Game *game) override;
    void onInput(Game *game, const SDL_Event &event) override;
    void onKeyInput(Game *game, const uint8_t *keys) override;
    void onUpdateInBackground(Game *game) override;

private:
    static const int IMAGE_LOAD_RATE = 50;
    
    bool isLoading() const;

    //Used for loading the game images
    std::vector<std::string> imageFilePaths;
    size_t currentImageFile;

    //Sprites
    FontSprite *loadingText;
};

#endif
