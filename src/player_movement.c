#include "player_movement.h"
#include <math.h>

#define WALL 1  /* Value indicating a wall in the mini-map */

/**
 * check_wall - Checks if a given position is within the world map.
 * @player: Pointer to the Player.
 * @x: x-coordinate to check.
 * @y: y-coordinate to check.
 *
 * Return: 1 if wall, 0 otherwise.
 */
int check_wall(Player *player, int x, int y)
{
	if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
	{
		return (player->mini_map[y][x] == WALL);
	}
	return (0);
}

/**
 * update_player_position - Updates player's position based on movement.
 * @player: Pointer to the Player.
 * @dx: Change in x-coordinate.
 * @dy: Change in y-coordinate.
 */
static void update_player_position(Player *player, float dx, float dy)
{
	if (!check_wall(player, (int)((player->x + dx) / TILE_SIZE),
		(int)(player->y / TILE_SIZE)))
	{
		player->x += dx;
	}
	if (!check_wall(player, (int)(player->x / TILE_SIZE),
		(int)((player->y + dy) / TILE_SIZE)))
	{
		player->y += dy;
	}
}

/**
 * handle_movement_keys - Handles key inputs for movement.
 * @player: Pointer to the Player.
 * @keys: Keyboard state.
 * @dx: Pointer to change in x-coordinate.
 * @dy: Pointer to change in y-coordinate.
 */
static void handle_movement_keys(Player *player, const Uint8 *keys,
	float *dx, float *dy)
{
	float speed = PLAYER_SPEED;
	float sin_a = sinf(player->angle);
	float cos_a = cosf(player->angle);

	*dx = 0;
	*dy = 0;

	if (keys[SDL_SCANCODE_W])
	{
		*dx += speed * cos_a;
		*dy += speed * sin_a;
	}
	if (keys[SDL_SCANCODE_S])
	{
		*dx -= speed * cos_a;
		*dy -= speed * sin_a;
	}
	if (keys[SDL_SCANCODE_A])
	{
		*dx += speed * sin_a;
		*dy -= speed * cos_a;
	}
	if (keys[SDL_SCANCODE_D])
	{
		*dx -= speed * sin_a;
		*dy += speed * cos_a;
	}
}

/**
 * player_movement - Moves the player and handles collisions.
 * @player: Pointer to the Player.
 * @keys: Keyboard state.
 */
void player_movement(Player *player, const Uint8 *keys)
{
	float dx;
	float dy;

	handle_movement_keys(player, keys, &dx, &dy);

	if (keys[SDL_SCANCODE_SPACE])
	{
		start_shotgun_animation(player->shotgun);
	}

	update_player_position(player, dx, dy);

	if (keys[SDL_SCANCODE_LEFT])
	{
		player->angle -= PLAYER_ROT_SPEED;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		player->angle += PLAYER_ROT_SPEED;
	}
}
