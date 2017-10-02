#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>
#include <string>

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
     * Image Constants
     **********************************
     */
    //First images to be loaded when the game launches
    static const char * const IMAGES_FIRST_TO_LOAD[];
    static const int IMAGES_FIRST_TO_LOAD_COUNT;
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

private:
	Constants() {}
	~Constants() {}
};

#endif
