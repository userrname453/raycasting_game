#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL2/SDL.h>
#include "player.h"
#include "map.h"

#define MINIMAP_SIZE 150

void draw_minimap(SDL_Renderer *renderer, Player *player, Map *map);

#endif /* MINIMAP_H */
