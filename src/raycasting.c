#include "raycasting.h"
#include <math.h>
#include "map.h"
#include "main.h"
#define C_PI 3.14159265358979323846264338327950288
#define HALF_FOV (C_PI / 6)    // Example field of view angle
#define NUM_RAYS 320   // Number of rays to cast
#define MAX_DEPTH 20   // Max depth for raycasting
#define DELTA_ANGLE (HALF_FOV * 2 / NUM_RAYS)
#define SCREEN_DIST ((WINDOW_WIDTH / 2) / tan(HALF_FOV))
#define SCALE 0.5  // Scale factor for wall heights

void ray_cast(Player* player, Map* map) {
    float ox = player->x;  // Player position
    float oy = player->y;
    int x_map = (int)(ox / TILE_SIZE);  // Player's current tile
    int y_map = (int)(oy / TILE_SIZE);
    float ray_angle = player->angle - HALF_FOV + 0.0001;  // Start angle of the first ray

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
        float depth = (depth_vert_final && depth_vert_final < depth_hor_final) ? depth_vert_final : depth_hor_final;
        if (!depth) depth = MAX_DEPTH * TILE_SIZE;  // If no wall was hit, set to max depth

        // Remove fishbowl effect
        depth *= cosf(player->angle - ray_angle);

        // Calculate wall height
        float wall_height = SCREEN_DIST * TILE_SIZE / (depth + 0.0001);

        // Draw the wall strip
        SDL_SetRenderDrawColor(player->renderer, 200, 200, 200, 255);  // Light gray color
        SDL_Rect wall_rect = {
            ray * SCALE,
            (WINDOW_HEIGHT - wall_height * SCALE) / 2,
            SCALE,
            wall_height * SCALE
        };
        SDL_RenderFillRect(player->renderer, &wall_rect);

        // Draw floor
        SDL_SetRenderDrawColor(player->renderer, 100, 100, 100, 255);  // Dark gray color
        SDL_Rect floor_rect = {
            ray * SCALE,
            (WINDOW_HEIGHT + wall_height * SCALE) / 2,
            SCALE,
            (WINDOW_HEIGHT - wall_height * SCALE) / 2
        };
        SDL_RenderFillRect(player->renderer, &floor_rect);

        // Move to the next ray
        ray_angle += DELTA_ANGLE;
    }
}

void draw_minimap(Player* player, Map* map) {
    int minimap_size = 150;
    int tile_size = minimap_size / MAP_WIDTH;

    // Draw background
    SDL_SetRenderDrawColor(player->renderer, 0, 0, 0, 200);
    SDL_Rect bg_rect = {0, 0, minimap_size, minimap_size};
    SDL_RenderFillRect(player->renderer, &bg_rect);

    // Draw walls
    SDL_SetRenderDrawColor(player->renderer, 255, 255, 255, 255);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map->mini_map[y][x] == 1) {
                SDL_Rect wall_rect = {x * tile_size, y * tile_size, tile_size, tile_size};
                SDL_RenderFillRect(player->renderer, &wall_rect);
            }
        }
    }

    // Draw player
    SDL_SetRenderDrawColor(player->renderer, 255, 0, 0, 255);
    SDL_Rect player_rect = {
        (int)(player->x / TILE_SIZE * tile_size) - 2,
        (int)(player->y / TILE_SIZE * tile_size) - 2,
        4, 4
    };
    SDL_RenderFillRect(player->renderer, &player_rect);

    // Draw player direction
    int dir_x = (int)(player->x / TILE_SIZE * tile_size + cosf(player->angle) * 10);
    int dir_y = (int)(player->y / TILE_SIZE * tile_size + sinf(player->angle) * 10);
    SDL_RenderDrawLine(player->renderer, player_rect.x + 2, player_rect.y + 2, dir_x, dir_y);
}