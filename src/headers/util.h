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
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "GahoodDug"

/* Colors and Alpha */
#define FULL_ALPHA 255
#define NO_ALPHA 0

/* *************************
 * Util consts and enums 
 * *************************
 */
typedef enum GameState {
    GAME_STATE_PLAY,
    GAME_STATE_PLAY_2,
    GAME_STATE_PLAY_3,
    GAME_STATE_PLAY_4,
    GAME_STATE_PLAY_5,
    GAME_STATE_EXIT
} GameState;

/* The Window Flags */
extern const uint32_t WINDOW_FLAGS;

/* *************************
 * Util methods 
 * *************************
 */
void gahood_utilFatalError(const char *);
void gahood_utilFatalSDLError(const char *);

#endif
