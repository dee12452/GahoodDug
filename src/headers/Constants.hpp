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
    static const char * const GAME_IMAGE_FOLDER;
    /******************
     ******************/

    
    /*
     **********************************
     * Image Ids
     **********************************
     */
    static const std::string IMAGE_ID_TEST;
    
    /*
     **********************************
     * Sprite Constants
     **********************************
     */
    static const uint8_t SPRITE_ALPHA_FULL;
    static const uint8_t SPRITE_ALPHA_NONE;

    /*
     **********************************
     * Sprite Constants
     **********************************
     */
    static const int TILE_WIDTH;
    static const int TILE_HEIGHT;

	/*
	**********************************
	* Map Files
	**********************************
	*/
	static const char * const MAP_TEST;

private:
	Constants() {}
	~Constants() {}
};

#endif
