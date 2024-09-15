// inc/game.h

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct {
    float posX, posY; // Player position
    float dirX, dirY; // Player direction
} Player;

void initializeSDL();
void cleanupSDL();
void gameLoop(Player *player);

#endif // GAME_H