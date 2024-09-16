#include <SDL2/SDL.h>
#include <stdio.h>
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "initialize.h"
#include "minimap.h"

int main(int argc, char *argv[])
{
    SDLContext context = initialize_sdl();
    if (!context.window || !context.renderer)
    {
        return 1;
    }

    // Create the map
    Map *map = create_map(context.renderer);

    // Create the player
    Player *player = create_player(context.renderer, map->mini_map);

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
        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255); // Black

        // Clear the screen
        SDL_RenderClear(context.renderer);


        // Update the player
        player_update(player);

        // Perform raycasting
        ray_cast(player, map);

        // Draw minimap
        draw_minimap(context.renderer,player, map);

        // Present the renderer
        SDL_RenderPresent(context.renderer);

        SDL_Delay(16); // Approx 60 FPS
    }

    // Cleanup
    destroy_player(player);
    destroy_map(map);
    cleanup_sdl(&context);
    return 0;
}