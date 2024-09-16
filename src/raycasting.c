#include "raycasting.h"
#include <math.h>

void ray_cast(Player *player, Map *map, RaycastingResult results[NUM_RAYS])
{
    float ray_angle = player->angle - HALF_FOV + 0.0001;

    for (int ray = 0; ray < NUM_RAYS; ray++)
    {
        float sin_a = sinf(ray_angle);
        float cos_a = cosf(ray_angle);

        // Calculate horizontal and vertical depths
        float x_hor, y_hor, depth_hor;
        calculate_horizontal_depth(player, map, sin_a, cos_a, &x_hor, &y_hor, &depth_hor);

        float x_vert, y_vert, depth_vert;
        calculate_vertical_depth(player, map, sin_a, cos_a, &x_vert, &y_vert, &depth_vert);

        // Determine which depth is smaller (horizontal or vertical)
        float depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;
        int direction = (depth_vert < depth_hor) ? 1 : 0;

        // Calculate the texture offset based on wall hit
        float offset = (depth_vert < depth_hor)
                     ? (cos_a > 0 ? fmod(y_vert, TILE_SIZE) : (TILE_SIZE - fmod(y_vert, TILE_SIZE)))
                     : (sin_a > 0 ? (TILE_SIZE - fmod(x_hor, TILE_SIZE)) : fmod(x_hor, TILE_SIZE));

        // Remove the fishbowl effect
        depth *= cos(player->angle - ray_angle);

        // Projection height
        float proj_height = SCREEN_DIST / (depth + 0.0001);

        // Store the result in the RaycastingResult struct
        results[ray].depth = depth;
        results[ray].proj_height = proj_height;
        results[ray].direction = direction;
        results[ray].offset = offset;

        // Set color and draw walls based on direction (light or dark gray)
        if (direction == 1)
        {
            SDL_SetRenderDrawColor(player->renderer, 211, 211, 211, SDL_ALPHA_OPAQUE); // Light grey
        }
        else
        {
            SDL_SetRenderDrawColor(player->renderer, 169, 169, 169, SDL_ALPHA_OPAQUE); // Dark grey
        }

        // Draw the wall slice
        SDL_Rect rect;
        rect.x = ray * SCALE;
        rect.y = (WINDOW_HEIGHT / 2) - proj_height / 2;
        rect.w = SCALE;
        rect.h = proj_height;
        SDL_RenderFillRect(player->renderer, &rect);

        ray_angle += DELTA_ANGLE;
    }
}
