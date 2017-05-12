#ifndef GAHOOD_UTIL_H
#define GAHOOD_UTIL_H

#include <stdint.h>

/* *************************
 * Util macros
 * *************************
 */

/* Delays in milliseconds */
#define DELAY_GAME_LOOP 5
#define DELAY_RENDER_LOOP 5
#define WINDOW_FPS 60

/* Window information */
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define GAME_WIDTH 720
#define GAME_HEIGHT 720
#define WINDOW_NAME "GahoodDug"

/* Colors and Alpha */
#define FULL_ALPHA 255
#define NO_ALPHA 0

/* Resource Files */
#define RES_FILE_DIRT "res/gahooddug_dirt.png"
#define RES_FILE_SPRITES "res/gahooddug_sprites.png"
#define RES_FILE_CONTROL_STICK_BG "res/gahooddug_control_stick_bg.png"
#define RES_FILE_CONTROL_STICK "res/gahooddug_control_stick.png"

/* *************************
 * Util consts and enums 
 * *************************
 */
typedef enum GameState {
    GAME_STATE_PLAY,
    GAME_STATE_NONE,
    GAME_STATE_EXIT
} GameState;

typedef enum Direction {
    DIRECTION_NONE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
} Direction;

/* The Window Flags */
extern const uint32_t WINDOW_FLAGS;
extern const uint32_t SDL_INIT_FLAGS;
extern const uint32_t IMG_INIT_FLAGS;

/* *************************
 * Util methods 
 * *************************
 */
void gahood_utilFatalError(const char *);
void gahood_utilFatalSDLError(const char *);

#endif
