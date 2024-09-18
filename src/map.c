#include "map.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * create_map - Creates and initializes a map from a file
 * @renderer: SDL renderer
 * @map_file: Path to the map file
 *
 * Return: Pointer to the created map or NULL if failed
 */
Map *create_map(SDL_Renderer *renderer, const char *map_file)
{
	Map *map;
	FILE *file;
	int y, x;

	map = (Map *)malloc(sizeof(Map));
	if (!map)
	{
		fprintf(stderr, "Failed to allocate memory for Map.\n");
		exit(1);
	}

	file = fopen(map_file, "r");
	if (!file)
	{
		fprintf(stderr, "Failed to open the map file: %s\n", map_file);
		free(map);
		exit(1);
	}

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (fscanf(file, "%d", &map->mini_map[y][x]) != 1)
			{
				fprintf(stderr, "Invalid map data in file: %s\n", map_file);
				fclose(file);
				free(map);
				exit(1);
			}
		}
	}

	fclose(file);

	map->renderer = renderer;
	return (map);
}

/**
 * destroy_map - Frees resources associated with a map
 * @map: Pointer to the map to destroy
 */
void destroy_map(Map *map)
{
	free(map);
}

/**
 * map_draw - Draws the map on the screen
 * @map: Pointer to the map to draw
 */
void map_draw(Map *map)
{
	int y, x;
	SDL_Rect rect;

	SDL_SetRenderDrawColor(map->renderer, 0, 0, 0, 255);
	SDL_RenderClear(map->renderer);

	SDL_SetRenderDrawColor(map->renderer, 128, 128, 128, 255);

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (map->mini_map[y][x] == 1)
			{
				rect.x = x * TILE_SIZE;
				rect.y = y * TILE_SIZE;
				rect.w = TILE_SIZE;
				rect.h = TILE_SIZE;
				SDL_RenderFillRect(map->renderer, &rect);
			}
		}
	}
}
