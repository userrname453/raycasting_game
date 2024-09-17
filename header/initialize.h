// initialize.h
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "shotgun.h"
#include "enemy.h"

// Function declarations
int initialize_sdl(SDL_Window **window, SDL_Renderer **renderer);
void cleanup_sdl(SDL_Window *window, SDL_Renderer *renderer);

Map *initialize_map(SDL_Renderer *renderer);
Player *initialize_player(SDL_Renderer *renderer, Map *map);
Shotgun *initialize_shotgun(SDL_Renderer *renderer);

void cleanup_resources(Player *player, Map *map, Shotgun *shotgun, Enemy *enemy);

#endif // INITIALIZE_H
