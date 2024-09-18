#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 100
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 1100

/**
 * struct Map - Represents the game map
 * @mini_map: 2D array representing the mini-map
 * @renderer: SDL renderer
 */
typedef struct Map
{
	int mini_map[MAP_HEIGHT][MAP_WIDTH];
	SDL_Renderer *renderer;
} Map;

Map *create_map(SDL_Renderer *renderer, const char *map_file);
void destroy_map(Map *map);
void map_draw(Map *map);

#endif /* MAP_H */
