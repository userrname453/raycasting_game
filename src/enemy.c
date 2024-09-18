#include "enemy.h"
#include <math.h>
#include "raycasting.h"

#define ENEMY_SIZE 64 /* Assuming the enemy sprite is 64x64 pixels */

/**
 * create_enemy - Creates and initializes an enemy
 * @renderer: SDL renderer
 * @map: Pointer to the map structure
 *
 * Return: Pointer to the created enemy or NULL if failed
 */
Enemy *create_enemy(SDL_Renderer *renderer, Map *map)
{
	Enemy *enemy;
	SDL_Surface *surface;
	int y, x;

	enemy = (Enemy *)malloc(sizeof(Enemy));
	if (!enemy)
	{
		fprintf(stderr, "Failed to allocate memory for Enemy.\n");
		return (NULL);
	}

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (map->mini_map[y][x] == 3)
			{
				enemy->x = x * TILE_SIZE + TILE_SIZE / 2;
				enemy->y = y * TILE_SIZE + TILE_SIZE / 2;
				break;
			}
		}
	}

	surface = IMG_Load("resources/enemy/enemy.png");
	enemy->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!enemy->texture)
	{
		fprintf(stderr, "Failed to create enemy texture: %s\n", SDL_GetError());
		free(enemy);
		return (NULL);
	}

	return (enemy);
}

/**
 * destroy_enemy - Frees resources associated with an enemy
 * @enemy: Pointer to the enemy to destroy
 */
void destroy_enemy(Enemy *enemy)
{
	if (enemy)
	{
		SDL_DestroyTexture(enemy->texture);
		free(enemy);
	}
}

/**
 * check_wall_intersection - Checks if there's a wall between two points
 * @map: Pointer to the map structure
 * @x1: X-coordinate of the first point
 * @y1: Y-coordinate of the first point
 * @x2: X-coordinate of the second point
 * @y2: Y-coordinate of the second point
 *
 * Return: 1 if there's a wall intersection, 0 otherwise
 */
int check_wall_intersection(Map *map, float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	float distance = sqrtf(dx * dx + dy * dy);
	float step = 1.0f; /* Step size for checking */
	float x = x1;
	float y = y1;
	float i;
	int map_x, map_y;

	dx /= distance;
	dy /= distance;

	for (i = 0; i < distance; i += step)
	{
		map_x = (int)(x / TILE_SIZE);
		map_y = (int)(y / TILE_SIZE);

		if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
		{
			if (map->mini_map[map_y][map_x] == 1)
				return (1); /* Wall intersection found */
		}

		x += dx * step;
		y += dy * step;
	}

	return (0); /* No wall intersection */
}

/**
 * draw_enemy - Draws the enemy on the screen
 * @renderer: SDL renderer
 * @enemy: Pointer to the enemy structure
 * @player: Pointer to the player structure
 * @map: Pointer to the map structure
 */
void draw_enemy(SDL_Renderer *renderer, Enemy *enemy, Player *player, Map *map)
{
	float dx = enemy->x - player->x;
	float dy = enemy->y - player->y;
	float distance = sqrtf(dx * dx + dy * dy);
	float enemy_angle = atan2f(dy, dx) - player->angle;
	float enemy_screen_x, enemy_height;
	SDL_Rect src_rect, dest_rect;

	if (enemy_angle < -C_PI)
		enemy_angle += 2 * C_PI;
	if (enemy_angle > C_PI)
		enemy_angle -= 2 * C_PI;

	if (fabsf(enemy_angle) < FOV / 2)
	{
		if (!check_wall_intersection(map, player->x, player->y, enemy->x, enemy->y))
		{
			enemy_screen_x = (0.5f * (enemy_angle / (FOV / 2)) + 0.5f) * WINDOW_WIDTH;
			enemy_height = WINDOW_HEIGHT / distance * ENEMY_SIZE;

			src_rect = (SDL_Rect){0, 0, ENEMY_SIZE, ENEMY_SIZE};
			dest_rect = (SDL_Rect){
				enemy_screen_x - enemy_height / 2,
				WINDOW_HEIGHT / 2 - enemy_height / 2,
				enemy_height,
				enemy_height
			};

			SDL_RenderCopy(renderer, enemy->texture, &src_rect, &dest_rect);
		}
	}
}
