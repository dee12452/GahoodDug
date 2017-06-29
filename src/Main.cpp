/** Need this include here for port to Android **/
#include <SDL2/SDL.h>
#include <stdio.h>
#include "headers/Gahoodmon.hpp"

void handleArgs(int, char **);

int main(int argc, char** argv) {
    /** At this point we don't need the input args 
     * So just print them out and let the user know **/
    handleArgs(argc, argv);
    Gahoodmon game;
    game.run();
    return 0;
}

void handleArgs(int argc, char *argv[]) {
    if(argc > 1) {
        printf("\nArguments will be ignored:\n");
        for(int i = 1; i < argc; i++) { printf("%s ", argv[i]); }
    }
}
