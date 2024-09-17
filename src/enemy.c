// enemy.c
#include "enemy.h"
#include <math.h>
#include "raycasting.h"
#define ENEMY_SIZE 64 // Assuming the enemy sprite is 64x64 pixels

Enemy *create_enemy(SDL_Renderer *renderer, Map *map)
{
    Enemy *enemy = (Enemy *)malloc(sizeof(Enemy));
    if (!enemy)
    {
        fprintf(stderr, "Failed to allocate memory for Enemy.\n");
        return NULL;
    }

    // Find the enemy position in the map
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map->mini_map[y][x] == 3)
            {
                enemy->x = x * TILE_SIZE + TILE_SIZE / 2;
                enemy->y = y * TILE_SIZE + TILE_SIZE / 2;
                break;
            }
        }
    }

    // Load enemy texture
    SDL_Surface *surface = IMG_Load("resources/enemy/enemy.png");
    if (!surface)
    {
        fprintf(stderr, "Failed to load enemy texture: %s\n", IMG_GetError());
        free(enemy);
        return NULL;
    }

    enemy->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!enemy->texture)
    {
        fprintf(stderr, "Failed to create enemy texture: %s\n", SDL_GetError());
        free(enemy);
        return NULL;
    }

    return enemy;
}

void destroy_enemy(Enemy *enemy)
{
    if (enemy)
    {
        SDL_DestroyTexture(enemy->texture);
        free(enemy);
    }
}

int check_wall_intersection(Map *map, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = sqrtf(dx * dx + dy * dy);
    float step = 1.0f; // Step size for checking

    dx /= distance;
    dy /= distance;

    float x = x1;
    float y = y1;

    for (float i = 0; i < distance; i += step)
    {
        int map_x = (int)(x / TILE_SIZE);
        int map_y = (int)(y / TILE_SIZE);

        if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
        {
            if (map->mini_map[map_y][map_x] == 1)
            {
                return 1; // Wall intersection found
            }
        }

        x += dx * step;
        y += dy * step;
    }

    return 0; // No wall intersection
}

void draw_enemy(SDL_Renderer* renderer, Enemy* enemy, Player* player, Map* map) {
    // Calculate angle and distance to enemy
    float dx = enemy->x - player->x;
    float dy = enemy->y - player->y;
    float distance = sqrtf(dx * dx + dy * dy);
    float enemy_angle = atan2f(dy, dx) - player->angle;

    // Adjust angle to be between -π and π
    if (enemy_angle < -C_PI) enemy_angle += 2 * C_PI;
    if (enemy_angle > C_PI) enemy_angle -= 2 * C_PI;

    // Check if enemy is in field of view
    if (fabsf(enemy_angle) < FOV / 2) {
        // Check if there's a wall between the player and the enemy
        if (!check_wall_intersection(map, player->x, player->y, enemy->x, enemy->y)) {
            // Calculate enemy screen position and size
            float enemy_screen_x = (0.5f * (enemy_angle / (FOV / 2)) + 0.5f) * WINDOW_WIDTH;
            float enemy_height = WINDOW_HEIGHT / distance * ENEMY_SIZE;

            // Define source and destination rectangles
            SDL_Rect src_rect = {0, 0, ENEMY_SIZE, ENEMY_SIZE};
            SDL_Rect dest_rect = {
                enemy_screen_x - enemy_height / 2,
                WINDOW_HEIGHT / 2 - enemy_height / 2,
                enemy_height,
                enemy_height
            };

            // Draw the enemy
            SDL_RenderCopy(renderer, enemy->texture, &src_rect, &dest_rect);
        }
    }
}
