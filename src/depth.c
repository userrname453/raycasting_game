#include "raycasting.h"
#include <math.h>

/**
 * calculate_horizontal_depth - Calculate depth for horizontal intersections
 * @player: Pointer to the player structure
 * @map: Pointer to the map structure
 * @sin_a: Sine of the angle
 * @cos_a: Cosine of the angle
 * @x_hor: Pointer to store horizontal x-coordinate
 * @y_hor: Pointer to store horizontal y-coordinate
 * @depth: Pointer to store the calculated depth
 */
void calculate_horizontal_depth(Player *player, Map *map, float sin_a,
				float cos_a, float *x_hor, float *y_hor, float *depth)
{
	float ox = player->x;
	float oy = player->y;
	int y_map = (int)(oy / TILE_SIZE);
	float dy, dx_hor, delta_depth_hor;
	int i, tile_hor_x, tile_hor_y;

	*y_hor = sin_a > 0 ? (y_map + 1) * TILE_SIZE : y_map * TILE_SIZE - 0.0001;
	dy = sin_a > 0 ? TILE_SIZE : -TILE_SIZE;
	*depth = (*y_hor - oy) / sin_a;
	*x_hor = ox + (*depth) * cos_a;
	delta_depth_hor = dy / sin_a;
	dx_hor = delta_depth_hor * cos_a;

	for (i = 0; i < MAX_DEPTH; i++)
	{
		tile_hor_x = (int)(*x_hor / TILE_SIZE);
		tile_hor_y = (int)(*y_hor / TILE_SIZE);

		if (tile_hor_x >= 0 && tile_hor_x < MAP_WIDTH &&
		    tile_hor_y >= 0 && tile_hor_y < MAP_HEIGHT)
		{
			if (map->mini_map[tile_hor_y][tile_hor_x] == 1)
				break;
		}
		else
		{
			break;
		}
		*x_hor += dx_hor;
		*y_hor += dy;
		*depth += delta_depth_hor;
	}
}

/**
 * calculate_vertical_depth - Calculate depth for vertical intersections
 * @player: Pointer to the player structure
 * @map: Pointer to the map structure
 * @sin_a: Sine of the angle
 * @cos_a: Cosine of the angle
 * @x_vert: Pointer to store vertical x-coordinate
 * @y_vert: Pointer to store vertical y-coordinate
 * @depth: Pointer to store the calculated depth
 */
void calculate_vertical_depth(Player *player, Map *map, float sin_a,
			      float cos_a, float *x_vert, float *y_vert, float *depth)
{
	float ox = player->x;
	float oy = player->y;
	int x_map = (int)(ox / TILE_SIZE);
	float dx, dy_vert, delta_depth_vert;
	int i, tile_vert_x, tile_vert_y;

	*x_vert = cos_a > 0 ? (x_map + 1) * TILE_SIZE : x_map * TILE_SIZE - 0.0001;
	dx = cos_a > 0 ? TILE_SIZE : -TILE_SIZE;
	*depth = (*x_vert - ox) / cos_a;
	*y_vert = oy + (*depth) * sin_a;
	delta_depth_vert = dx / cos_a;
	dy_vert = delta_depth_vert * sin_a;

	for (i = 0; i < MAX_DEPTH; i++)
	{
		tile_vert_x = (int)(*x_vert / TILE_SIZE);
		tile_vert_y = (int)(*y_vert / TILE_SIZE);

		if (tile_vert_x >= 0 && tile_vert_x < MAP_WIDTH &&
		    tile_vert_y >= 0 && tile_vert_y < MAP_HEIGHT)
		{
			if (map->mini_map[tile_vert_y][tile_vert_x] == 1)
				break;
		}
		else
		{
			break;
		}
		*x_vert += dx;
		*y_vert += dy_vert;
		*depth += delta_depth_vert;
	}
}
