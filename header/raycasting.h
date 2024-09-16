#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include "player.h"
#include "map.h"
#include <math.h>

// Function prototypes
void ray_cast(Player* player, Map* map);

#endif // RAYCASTING_H
