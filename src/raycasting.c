#include "raycasting.h"
#include <math.h>

void ray_cast(Player *player, Map *map)
{
    float ray_angle = player->angle - HALF_FOV + 0.0001;

    for (int ray = 0; ray < NUM_RAYS; ray++)
    {
        float sin_a = sinf(ray_angle);
        float cos_a = cosf(ray_angle);

        // Use the new functions to calculate depths
        float depth_hor = calculate_horizontal_depth(player, map, ray_angle, sin_a, cos_a);
        float depth_vert = calculate_vertical_depth(player, map, ray_angle, sin_a, cos_a);

        int direction = (depth_vert < depth_hor) ? 1 : 0;
        float depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;

        // Remove fishbowl effect
        depth *= cos(player->angle - ray_angle);

        // Projection
        float proj_height = SCREEN_DIST / (depth + 0.0001);

        // Set color based on direction
        if (direction == 1)
        {
            SDL_SetRenderDrawColor(player->renderer, 211, 211, 211, SDL_ALPHA_OPAQUE); // Light grey
        }
        else
        {
            SDL_SetRenderDrawColor(player->renderer, 169, 169, 169, SDL_ALPHA_OPAQUE); // Dark grey
        }

        SDL_Rect rect;
        rect.x = ray * SCALE;
        rect.y = (WINDOW_HEIGHT / 2) - proj_height / 2;
        rect.w = SCALE;
        rect.h = proj_height;

        SDL_RenderFillRect(player->renderer, &rect);

        ray_angle += DELTA_ANGLE;
    }
}
