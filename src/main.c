#include <SDL2/SDL.h>
#include <stdio.h>
#include "map.h"    // Include the map header file
#include "player.h" // Include the player header file
#include "raycasting.h"

#define WINDOW_WIDTH 1100
#define WINDOW_HEIGHT 1100

int main(int argc, char *argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow(
        "Map Display",           // Window title
        SDL_WINDOWPOS_UNDEFINED, // Initial x position
        SDL_WINDOWPOS_UNDEFINED, // Initial y position
        WINDOW_WIDTH,            // Width, in pixels
        WINDOW_HEIGHT,           // Height, in pixels
        SDL_WINDOW_SHOWN         // Window flags
    );
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                  // Window
        -1,                      // Renderer index
        SDL_RENDERER_ACCELERATED // Renderer flags
    );
    if (renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create the map
    Map *map = create_map(renderer);

    // Create the player
    Player *player = create_player(renderer, map->mini_map);

    // Main loop
    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Set render draw color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw sky
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);  // Light blue color
        SDL_Rect sky_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
        SDL_RenderFillRect(renderer, &sky_rect);

        // Update the player
        player_update(player);

        // Perform raycasting
        ray_cast(player, map);

        // Draw minimap
        draw_minimap(player, map);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Approx 60 FPS
    }

    // Cleanup
    destroy_player(player);
    destroy_map(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
