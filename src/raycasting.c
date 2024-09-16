#include "raycasting.h"
#include <math.h>
#include "map.h"
#include "main.h"

#define C_PI 3.14159265358979323846264338327950288
#define FOV (C_PI / 6)
#define HALF_FOV (FOV / 2)    // Example field of view angle
#define NUM_RAYS (WIDTH / 2)     // Number of rays to cast
#define MAX_DEPTH 20   // Max depth for raycasting
#define DELTA_ANGLE (HALF_FOV * 2 / NUM_RAYS)
#define SCREEN_DIST ((WIDTH / 2) / tan(HALF_FOV))
#define SCALE 2  // Scale factor for wall heights
#define HALF_WIDTH  (WIDTH / 2)
#define HALF_HEIGHT  (HEIGHT / 2)

void ray_cast(Player* player, Map* map) {
    float ox = player->x;  // Player position
    float oy = player->y;

    int x_map = (int)(ox / TILE_SIZE);  // Player's current tile
    int y_map = (int)(oy / TILE_SIZE);

    float ray_angle = player ->angle - HALF_FOV + 0.0001;

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

        int tile_hor_x, tile_hor_y;
        float depth_hor_final = 0;

        // Check horizontal intersections
        for (int i = 0; i < MAX_DEPTH; i++) {
            tile_hor_x = (int)(x_hor / TILE_SIZE);
            tile_hor_y = (int)(y_hor / TILE_SIZE);
            // Bounds checking
            if (tile_hor_x >= 0 && tile_hor_x < MAP_WIDTH && tile_hor_y >= 0 && tile_hor_y < MAP_HEIGHT) {
                if (map->mini_map[tile_hor_y][tile_hor_x] == 1) {  // If there's a wall
                    depth_hor_final = depth_hor;
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

        int tile_vert_x, tile_vert_y;
        float depth_vert_final = 0;

        // Check vertical intersections
        for (int i = 0; i < MAX_DEPTH; i++) {
            tile_vert_x = (int)(x_vert / TILE_SIZE);
            tile_vert_y = (int)(y_vert / TILE_SIZE);
            // Bounds checking
            if (tile_vert_x >= 0 && tile_vert_x < MAP_WIDTH && tile_vert_y >= 0 && tile_vert_y < MAP_HEIGHT) {
                if (map->mini_map[tile_vert_y][tile_vert_x] == 1) {  // If there's a wall
                    depth_vert_final = depth_vert;
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
        float depth;
        if (!depth_hor_final) {
            depth = depth_vert_final;
        } else if (!depth_vert_final) {
            depth = depth_hor_final;
        } else {
            depth = (depth_vert_final < depth_hor_final) ? depth_vert_final : depth_hor_final;
        }
            // Print debug information
        printf("Ray %d:\n", ray);
        printf("  Horizontal Depth: %f\n", depth_hor_final);
        printf("  Vertical Depth: %f\n", depth_vert_final);
        printf("  final Depth: %f\n", depth);

        // Remove fishbowl effect
        depth *= cosf(player->angle - ray_angle);

        // Calculate wall height
        float proj_height = SCREEN_DIST / (depth + 0.0001);

        // Draw the wall strip
        // Set the draw color to white
        SDL_SetRenderDrawColor(player->renderer, 255, 255, 255, 255);  // Light gray color

        // Define the rectangle representing the wall strip
        SDL_Rect wall_rect = {
            ray * SCALE,  // X position
            (HEIGHT / 2 - proj_height / 2),  // Y position
            SCALE,  // Width
            proj_height   // Height
        };

        // Render the rectangle (the wall strip)
        SDL_RenderFillRect(player->renderer, &wall_rect);

        // // Draw floor
        // SDL_SetRenderDrawColor(player->renderer, 100, 100, 100, 255);  // Dark gray color
        // SDL_Rect floor_rect = {
        //     ray * SCALE,
        //     (HEIGHT + proj_height * SCALE) / 2,
        //     SCALE,
        //     (HEIGHT - proj_height * SCALE) / 2
        // };
        // SDL_RenderFillRect(player->renderer, &floor_rect);

        // Move to the next ray
        ray_angle += DELTA_ANGLE;
    }
}