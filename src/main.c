#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "initialize.h"
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "minimap.h"
#include "shotgun.h"
#include "enemy.h"
int main(int argc, char *argv[])
{
    // Variables for window and renderer
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialize SDL, window, and renderer
    if (!initialize_sdl(&window, &renderer))
    {
        return 1;
    }

    // Initialize map, player, and shotgun
    Map *map = create_map(renderer, "map.txt");
    Shotgun *shotgun = create_shotgun(renderer);
    Player *player = create_player(renderer, map->mini_map, shotgun);
    Enemy *enemy = create_enemy(renderer, map);

    if (!enemy)
    {
        fprintf(stderr, "Failed to create enemy!\n");
        cleanup_resources(player, map, shotgun,enemy);
        cleanup_sdl(window, renderer);
        return 1;
    }

    if (!player || !map || !shotgun)
    {
        fprintf(stderr, "Failed to initialize resources!\n");
        cleanup_resources(player, map, shotgun,enemy);
        cleanup_sdl(window, renderer);
        return 1;
    }

    RaycastingResult results[NUM_RAYS];

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

        player_update(player);

        ray_cast(player, map, results);

        render_shotgun(renderer, shotgun);

        draw_enemy(renderer, enemy, player, map);
        // Draw the mini-map
        draw_minimap(renderer, player, map);

        // Present the renderer
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Approx 60 FPS
    }

    // Cleanup resources and SDL
    cleanup_resources(player, map, shotgun, enemy);
    cleanup_sdl(window, renderer);

    return 0;
}
