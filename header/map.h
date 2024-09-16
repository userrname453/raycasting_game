#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 100  // Define tile size
#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 1100

typedef struct {
    int mini_map[MAP_HEIGHT][MAP_WIDTH];
    SDL_Renderer* renderer;
} Map;

// Function prototypes
Map* create_map(SDL_Renderer* renderer);
void destroy_map(Map* map);
void map_draw(Map* map);

#endif // MAP_H
