#include "map.h"
#include <stdlib.h>
#include <stdio.h>

// Mini-map definition (using 0 for empty and 1 for walls)
// static int mini_map[MAP_HEIGHT][MAP_WIDTH] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 3, 1},
//     {1, 0, 1, 1, 0, 1, 1, 0, 1, 1},
//     {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
//     {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// Function to load the map from a text file
Map *create_map(SDL_Renderer *renderer, const char *map_file)
{
    Map *map = (Map *)malloc(sizeof(Map));
    if (!map)
    {
        fprintf(stderr, "Failed to allocate memory for Map.\n");
        exit(1);
    }

    // Open the map file
    FILE *file = fopen(map_file, "r");
    if (!file)
    {
        fprintf(stderr, "Failed to open the map file: %s\n", map_file);
        free(map);
        exit(1);
    }

    // Read the map data from the file
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
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

    // Close the file
    fclose(file);

    map->renderer = renderer;
    return map;
}

// Function to destroy a Map
void destroy_map(Map *map)
{
    free(map);
}

// Draw the map on the screen
void map_draw(Map *map)
{
    // Set render draw color to black for the background
    SDL_SetRenderDrawColor(map->renderer, 0, 0, 0, 255); // Black
    SDL_RenderClear(map->renderer);                      // Clear the screen with black color

    // Set render draw color to white for walls
    SDL_SetRenderDrawColor(map->renderer, 128, 128, 128, 255); // White

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map->mini_map[y][x] == 1)
            { // Draw walls
                SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

                // Draw filled rectangle for walls
                SDL_RenderFillRect(map->renderer, &rect);
            }
        }
    }
}
