#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "shotgun.h"
#include "enemy.h"

int initialize_sdl(SDL_Window **window, SDL_Renderer **renderer);

#endif /* INITIALIZE_H */
