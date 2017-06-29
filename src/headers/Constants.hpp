#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>

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
    /******************
     ******************/

private:
    Constants();
    ~Constants();
};

#endif