#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>
#include <string>

struct SDL_Color;

class Constants {
public:
    /*
     **********************************
     * Window Constants
     **********************************
     */
    static const char * GAME_TITLE;
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const uint32_t WINDOW_FLAGS;
    /******************
     ******************/


    /*
     **********************************
     * Game Constants
     **********************************
     */
    static const uint8_t GAME_LOOP_DELAY;
    static const uint8_t RENDER_LOOP_DELAY;
    static const uint8_t TARGET_FPS;
    static const char * const GAME_THREAD_NAME;
    static const char * const GAME_RES_FOLDER;
    /******************
     ******************/


    /*
     **********************************
     * File Constants
     **********************************
     */
    //File extensions
    static const char * const IMAGE_FILE_EXTENSION;
    static const char * const TILESET_FILE_EXTENSION;
    static const char * const MAP_FILE_EXTENSION;
    static const char * const FONT_FILE_EXTENSION;
    
    //Font files
    static const char * const FONT_JOYSTIX;
    /******************
     ******************/

    
    /*
     **********************************
     * Color Constants
     **********************************
     */
	static const SDL_Color COLOR_BLACK;
	static const SDL_Color COLOR_WHITE;
	static const SDL_Color COLOR_GREY;
	static const SDL_Color COLOR_RED;
	static const SDL_Color COLOR_BLUE;
	static const SDL_Color COLOR_GREEN;
	static const SDL_Color COLOR_YELLOW;
    /******************
	******************/
    
    /*
     **********************************
     * Sprite Constants
     **********************************
     */
	//Alpha constants for the sprite
    static const uint8_t SPRITE_ALPHA_FULL;
    static const uint8_t SPRITE_ALPHA_NONE;
	/******************
	******************/
    
    /*
     **********************************
     * Map Constants
     **********************************
     */
	static const char * const MAP_TEST;
    /******************
	******************/

private:
	Constants() {}
	~Constants() {}

};

#endif
