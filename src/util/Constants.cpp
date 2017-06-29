#include "../headers/Constants.hpp"
#include <SDL2/SDL.h>

/*
 * WINDOW CONST */
const char * Constants::GAME_TITLE = "Gahoodmon";
const int Constants::WINDOW_WIDTH = 500;
const int Constants::WINDOW_HEIGHT = 500;
const uint32_t Constants::WINDOW_FLAGS = SDL_WINDOW_OPENGL; 

/*
 * GAME CONST */
const uint8_t Constants::GAME_LOOP_DELAY = 5;
const uint8_t Constants::RENDER_LOOP_DELAY = 5;
const uint8_t Constants::TARGET_FPS = 60;
