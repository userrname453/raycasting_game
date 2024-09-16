#include "raycasting.h"
#include <math.h>

#define C_PI 3.14159265358979323846264338327950288
#define HALF_FOV (C_PI / 6)
#define NUM_RAYS 1
#define MAX_DEPTH 20
#define DELTA_ANGLE (HALF_FOV * 2 / NUM_RAYS)

void ray_cast(Player* player, Map* map) {
    float ox = player->x;  // Player position
    float oy = player->y;
    int x_map = (int)(ox / TILE_SIZE);  // Player's current tile
    int y_map = (int)(oy / TILE_SIZE);
    float ray_angle = player->angle + 0.0001;  // Start angle of the first ray

    for (int ray = 0; ray < NUM_RAYS; ray++) {
        float sin_a = sinf(ray_angle);
        float cos_a = cosf(ray_angle);

        // Horizontals
        float y_hor = sin_a > 0 ? (y_map + 1) * TILE_SIZE : y_map * TILE_SIZE - 0.0001;
        float dy = sin_a > 0 ? TILE_SIZE : -TILE_SIZE;
        float depth_hor = (y_hor - oy) / sin_a;
        float x_hor = ox + depth_hor * cos_a;
        float delta_depth_hor = dy / sin_a;
        float dx_hor = delta_depth_hor * cos_a;

        // Check horizontal intersections
        for (int i = 0; i < MAX_DEPTH; i++) {
            int tile_hor_x = (int)(x_hor / TILE_SIZE);
            int tile_hor_y = (int)(y_hor / TILE_SIZE);
            // Bounds checking
            if (tile_hor_x >= 0 && tile_hor_x < MAP_WIDTH && tile_hor_y >= 0 && tile_hor_y < MAP_HEIGHT) {
                if (map->mini_map[tile_hor_y][tile_hor_x] == 1) {  // If there's a wall
                    break;
                }
            } else {
                break;  // Out of bounds, stop checking this ray
            }
            x_hor += dx_hor;
            y_hor += dy;
            depth_hor += delta_depth_hor;
        }

        // Verticals
        float x_vert = cos_a > 0 ? (x_map + 1) * TILE_SIZE : x_map * TILE_SIZE - 0.0001;
        float dx = cos_a > 0 ? TILE_SIZE : -TILE_SIZE;
        float depth_vert = (x_vert - ox) / cos_a;
        float y_vert = oy + depth_vert * sin_a;
        float delta_depth_vert = dx / cos_a;
        float dy_vert = delta_depth_vert * sin_a;

        // Check vertical intersections
        for (int i = 0; i < MAX_DEPTH; i++) {
            int tile_vert_x = (int)(x_vert / TILE_SIZE);
            int tile_vert_y = (int)(y_vert / TILE_SIZE);
            // Bounds checking
            if (tile_vert_x >= 0 && tile_vert_x < MAP_WIDTH && tile_vert_y >= 0 && tile_vert_y < MAP_HEIGHT) {
                if (map->mini_map[tile_vert_y][tile_vert_x] == 1) {  // If there's a wall
                    break;
                }
            } else {
                break;  // Out of bounds, stop checking this ray
            }
            x_vert += dx;
            y_vert += dy_vert;
            depth_vert += delta_depth_vert;
        }

        // Determine the closer intersection
        float depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;
        printf("depth is : %f",depth);
        // Drawing ray for debugging
        SDL_SetRenderDrawColor(player->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);  // Yellow color
        SDL_RenderDrawLine(player->renderer, (int)ox, (int)oy,
            (int)(ox + depth * cos_a), (int)(oy + depth * sin_a));

        // Move to the next ray
        ray_angle += DELTA_ANGLE;
    }
}
