#include "raycasting.h"
#include <math.h>

void calculate_horizontal_depth(Player *player, Map *map, float sin_a, float cos_a, float *x_hor, float *y_hor, float *depth)
{
    float ox = player->x;
    float oy = player->y;
    int y_map = (int)(oy / TILE_SIZE);

    *y_hor = sin_a > 0 ? (y_map + 1) * TILE_SIZE : y_map * TILE_SIZE - 0.0001;
    float dy = sin_a > 0 ? TILE_SIZE : -TILE_SIZE;
    *depth = (*y_hor - oy) / sin_a;
    *x_hor = ox + (*depth) * cos_a;
    float delta_depth_hor = dy / sin_a;
    float dx_hor = delta_depth_hor * cos_a;

    for (int i = 0; i < MAX_DEPTH; i++)
    {
        int tile_hor_x = (int)(*x_hor / TILE_SIZE);
        int tile_hor_y = (int)(*y_hor / TILE_SIZE);

        if (tile_hor_x >= 0 && tile_hor_x < MAP_WIDTH && tile_hor_y >= 0 && tile_hor_y < MAP_HEIGHT)
        {
            if (map->mini_map[tile_hor_y][tile_hor_x] == 1)
            {
                break;
            }
        }
        else
        {
            break;
        }
        *x_hor += dx_hor;
        *y_hor += dy;
        *depth += delta_depth_hor;
    }
}


void calculate_vertical_depth(Player *player, Map *map, float sin_a, float cos_a, float *x_vert, float *y_vert, float *depth)
{
    float ox = player->x;
    float oy = player->y;
    int x_map = (int)(ox / TILE_SIZE);

    *x_vert = cos_a > 0 ? (x_map + 1) * TILE_SIZE : x_map * TILE_SIZE - 0.0001;
    float dx = cos_a > 0 ? TILE_SIZE : -TILE_SIZE;
    *depth = (*x_vert - ox) / cos_a;
    *y_vert = oy + (*depth) * sin_a;
    float delta_depth_vert = dx / cos_a;
    float dy_vert = delta_depth_vert * sin_a;

    for (int i = 0; i < MAX_DEPTH; i++)
    {
        int tile_vert_x = (int)(*x_vert / TILE_SIZE);
        int tile_vert_y = (int)(*y_vert / TILE_SIZE);

        if (tile_vert_x >= 0 && tile_vert_x < MAP_WIDTH && tile_vert_y >= 0 && tile_vert_y < MAP_HEIGHT)
        {
            if (map->mini_map[tile_vert_y][tile_vert_x] == 1)
            {
                break;
            }
        }
        else
        {
            break;
        }
        *x_vert += dx;
        *y_vert += dy_vert;
        *depth += delta_depth_vert;
    }
}
