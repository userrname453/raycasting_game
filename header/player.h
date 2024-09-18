#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>
#include "map.h"
#include "shotgun.h"
#include "player_movement.h"


#define PLAYER_POS_X 150
#define PLAYER_POS_Y 150
#define PLAYER_ANGLE 0
#define PLAYER_SPEED 2.5
#define PLAYER_ROT_SPEED 0.035
#define C_PI 3.14159265358979323846264338327950288
#define TILE_SIZE 100

/**
 * struct Player - Represents the player in the game
 * @x: x-coordinate of the player
 * @y: y-coordinate of the player
 * @angle: Angle of the player's view
 * @renderer: SDL renderer
 * @mini_map: 2D array representing the mini-map
 * @shotgun: Pointer to the player's shotgun
 */
typedef struct Player
{
	float x, y;
	float angle;
	SDL_Renderer *renderer;
	int mini_map[MAP_HEIGHT][MAP_WIDTH];
	Shotgun *shotgun;
} Player;

Player *create_player(SDL_Renderer *renderer,
					  int mini_map[MAP_HEIGHT][MAP_WIDTH], Shotgun *shotgun);
void destroy_player(Player *player);
void player_update(Player *player, const Uint8 *keys);
int is_player_facing_enemy(Player *player, float ex, float ey);
void player_movement(Player *player, const Uint8 *keys);

#endif /* PLAYER_H */
