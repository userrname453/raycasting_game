#ifndef CLEANUP_H
#define CLEANUP_H

#include <SDL2/SDL.h>
#include "map.h"
#include "player.h"
#include "shotgun.h"
#include "enemy.h"
#include "raycasting.h"
#include "game.h"



void cleanup_sdl(SDL_Window *window, SDL_Renderer *renderer);
void cleanup_resources(Player *player, Map *map, Shotgun *shotgun,
Enemy *enemy);
void cleanup_all(GameState *state);

#endif /* CLEANUP_H */
