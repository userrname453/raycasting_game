#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>
#include "map.h" // Correct include guard and path
#include "shotgun.h"

#define PLAYER_POS_X 150
#define PLAYER_POS_Y 150
#define PLAYER_ANGLE 0
#define PLAYER_SPEED 2.5
#define PLAYER_ROT_SPEED 0.035
#define C_PI 3.14159265358979323846264338327950288
#define TILE_SIZE 100

typedef struct
{
    float x, y;
    float angle;
    SDL_Renderer *renderer;
    int mini_map[MAP_HEIGHT][MAP_WIDTH]; // 2D array for the map
    Shotgun *shotgun;                    // Add this line

} Player;

// Function declarations
Player *create_player(SDL_Renderer *renderer, int mini_map[MAP_HEIGHT][MAP_WIDTH], Shotgun *shotgun);
void destroy_player(Player *player);
void player_movement(Player *player, const Uint8 *keys);
void player_check_wall_collision(Player *player, float dx, float dy);
void player_draw(Player *player);
void player_update(Player *player,const Uint8 *keys);
int is_player_facing_enemy(Player *player, float ex, float ey );

#endif // PLAYER_H
