#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "player.h"
#include "map.h"
#include <SDL2/SDL.h>


#define C_PI 3.14159265358979323846264338327950288
#define HALF_FOV (C_PI / 6)
#define NUM_RAYS 100
#define MAX_DEPTH 20
#define DELTA_ANGLE (HALF_FOV * 2 / NUM_RAYS)
#define SCREEN_DIST (WINDOW_WIDTH / 2 / tan(HALF_FOV) * 100)
#define SCALE (WINDOW_WIDTH / NUM_RAYS)

typedef struct {
    float depth;
    float proj_height;
    int direction;
    float offset;
} RaycastingResult;

void calculate_horizontal_depth(Player *player, Map *map, float sin_a, float cos_a, float *x_hor, float *y_hor, float *depth);
void calculate_vertical_depth(Player *player, Map *map, float sin_a, float cos_a, float *x_vert, float *y_vert, float *depth);
void ray_cast(Player *player, Map *map, RaycastingResult results[NUM_RAYS]);

#endif // RAYCASTING_H
