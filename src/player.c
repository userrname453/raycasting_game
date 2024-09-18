#include <stdlib.h>
#include "player.h"
#include "player_movement.h"
#include <stdio.h>

/**
 * create_player - Creates and initializes a Player
 * @renderer: SDL renderer
 * @mini_map: 2D array representing the map
 * @shotgun: Pointer to the Shotgun
 *
 * Return: Pointer to the created Player or NULL if failed
 */
Player *create_player(SDL_Renderer *renderer,
		int mini_map[MAP_HEIGHT][MAP_WIDTH], Shotgun *shotgun)
{
	Player *player;
	int y, x;

	player = (Player *)malloc(sizeof(Player));
	if (!player)
	{
		fprintf(stderr, "Failed to allocate memory for Player.\n");
		exit(1);
	}
	player->x = PLAYER_POS_X;
	player->y = PLAYER_POS_Y;
	player->angle = PLAYER_ANGLE;
	player->renderer = renderer;

	for (y = 0; y < MAP_HEIGHT; y++)
		for (x = 0; x < MAP_WIDTH; x++)
			player->mini_map[y][x] = mini_map[y][x];

	player->shotgun = shotgun;

	return (player);
}

/**
 * is_player_facing_enemy - Checks if player is facing the enemy
 * @player: Pointer to the Player
 * @ex: Enemy x-coordinate
 * @ey: Enemy y-coordinate
 *
 * Return: 1 if facing, 0 otherwise
 */
int is_player_facing_enemy(Player *player, float ex, float ey)
{
	float dx, dy, angle_to_enemy, angle_diff;

	dx = ex - player->x;
	dy = ey - player->y;
	angle_to_enemy = atan2f(dy, dx);
	angle_diff = angle_to_enemy - player->angle;

	if (angle_diff < -C_PI)
		angle_diff += 2 * C_PI;
	if (angle_diff > C_PI)
		angle_diff -= 2 * C_PI;

	return (fabsf(angle_diff) < (C_PI / 6));
}

/**
 * destroy_player - Destroys a Player
 * @player: Pointer to the Player to destroy
 */
void destroy_player(Player *player)
{
	destroy_shotgun(player->shotgun);
	free(player);
}

/**
 * player_update - Updates the player (movement and drawing)
 * @player: Pointer to the Player
 * @keys: Keyboard state
 */
void player_update(Player *player, const Uint8 *keys)
{
	player_movement(player, keys);
	update_shotgun(player->shotgun);
}
