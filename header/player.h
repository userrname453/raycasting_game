#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>

#define PLAYER_POS_X 150
#define PLAYER_POS_Y 150
#define PLAYER_ANGLE 0
#define PLAYER_SPEED 0.1
#define PLAYER_ROT_SPEED 0.002
#define WIDTH 100

typedef struct {
    float x, y;
    float angle;
    SDL_Renderer* renderer;
    Uint8* world_map;  // Pointer to the game world map
} Player;

// Function declarations
Player* create_player(SDL_Renderer* renderer, Uint8* world_map);
void destroy_player(Player* player);
void player_movement(Player* player, const Uint8* keys);
void player_check_wall_collision(Player* player, float dx, float dy);
void player_draw(Player* player);
void player_update(Player* player);

#endif // PLAYER_H
