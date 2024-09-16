#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>
#include "map.h"  // Correct include guard and path

#define PLAYER_POS_X 150
#define PLAYER_POS_Y 150
#define PLAYER_ANGLE 0
#define PLAYER_SPEED 2.5
#define PLAYER_ROT_SPEED 0.009

#define TILE_SIZE 100

typedef struct {
    float x, y;
    float angle;
    SDL_Renderer* renderer;
    int mini_map[MAP_HEIGHT][MAP_WIDTH];  // 2D array for the map
} Player;

// Function declarations
Player* create_player(SDL_Renderer* renderer, int mini_map[MAP_HEIGHT][MAP_WIDTH]);
void destroy_player(Player* player);
void player_movement(Player* player, const Uint8* keys);
void player_check_wall_collision(Player* player, float dx, float dy);
void player_draw(Player* player);
void player_update(Player* player);

#endif // PLAYER_H
