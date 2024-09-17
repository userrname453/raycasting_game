#include "raycasting.h"
#include "draw_walls.h"
#include "draw_sky.h"
#include "draw_floor.h"

void ray_cast(Player *player, Map *map, RaycastingResult results[NUM_RAYS]) {
    float ray_angle = player->angle - HALF_FOV + 0.0001;

    for (int ray = 0; ray < NUM_RAYS; ray++) {
        float sin_a = sinf(ray_angle);
        float cos_a = cosf(ray_angle);

        float x_hor, y_hor, depth_hor;
        calculate_horizontal_depth(player, map, sin_a, cos_a, &x_hor, &y_hor, &depth_hor);

        float x_vert, y_vert, depth_vert;
        calculate_vertical_depth(player, map, sin_a, cos_a, &x_vert, &y_vert, &depth_vert);

        float depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;
        int direction = (depth_vert < depth_hor) ? 1 : 0;

        float offset = (depth_vert < depth_hor)
                     ? (cos_a > 0 ? fmod(y_vert, 100) : (1 - fmod(y_vert, 100)))
                     : (sin_a > 0 ? (1 - fmod(x_hor, 100)) : fmod(x_hor, 100));

        depth *= cos(player->angle - ray_angle); // Remove fishbowl effect
        float proj_height = SCREEN_DIST / (depth + 0.0001);

        // Store the ray result
        results[ray] = (RaycastingResult) { depth, proj_height, direction, offset };

        ray_angle += DELTA_ANGLE;
    }

    // Drawing order: sky, floor, walls
    draw_sky(player->renderer);
    draw_floor(player->renderer);
    draw_walls(player->renderer, results);
}
