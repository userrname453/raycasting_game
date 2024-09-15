// src/main.c

#include <SDL2/SDL.h>
#include "game.h"

int main(int argc, char *argv[]) {
    Player player = {1.5f, 1.5f, 1.0f, 0.0f}; // Initial player position and direction

    initializeSDL();
    gameLoop(&player);
    cleanupSDL();

    return 0;
}