#include "minimap.h"
#include <math.h>

#define MINIMAP_SIZE 150

void draw_minimap(SDL_Renderer* renderer, Player* player, Map* map) {
    int tile_size = MINIMAP_SIZE / MAP_WIDTH;

    // Draw background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect bg_rect = {0, 0, MINIMAP_SIZE, MINIMAP_SIZE};
    SDL_RenderFillRect(renderer, &bg_rect);

    // Draw walls
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map->mini_map[y][x] == 1) {
                SDL_Rect wall_rect = {x * tile_size, y * tile_size, tile_size, tile_size};
                SDL_RenderFillRect(renderer, &wall_rect);
            }
        }
    }

    // Draw player
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect player_rect = {
        (int)(player->x / TILE_SIZE * tile_size) - 2,
        (int)(player->y / TILE_SIZE * tile_size) - 2,
        4, 4
    };
    SDL_RenderFillRect(renderer, &player_rect);

    // Draw player direction
    int dir_x = (int)(player->x / TILE_SIZE * tile_size + cosf(player->angle) * 10);
    int dir_y = (int)(player->y / TILE_SIZE * tile_size + sinf(player->angle) * 10);
    SDL_RenderDrawLine(renderer, player_rect.x + 2, player_rect.y + 2, dir_x, dir_y);
}