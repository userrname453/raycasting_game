#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "map.h"    // Include the map header file
#include "player.h" // Include the player header file
#include "raycasting.h"
#include "minimap.h"
#include "shotgun.h"

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

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create the map
    Map *map = create_map(renderer, "map.txt");

    // Create the player
    Player *player = create_player(renderer, map->mini_map);
    RaycastingResult results[NUM_RAYS];

    // Create the shotgun
    Shotgun *shotgun = create_shotgun(renderer);
    if (!shotgun)
    {
        fprintf(stderr, "Failed to create shotgun!\n");
        destroy_player(player);
        destroy_map(map);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

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
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    start_shotgun_animation(shotgun);
                }
            }
        }

        // Set render draw color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black

        // Clear the screen
        SDL_RenderClear(renderer);

        player_update(player);
        ray_cast(player, map, results);

        // Draw the mini-map
        draw_minimap(renderer, player, map);

        // Update and render the shotgun
        update_shotgun(shotgun);
        render_shotgun(renderer, shotgun);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Approx 60 FPS
    }

    // Cleanup
    destroy_shotgun(shotgun);
    destroy_player(player);
    destroy_map(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
