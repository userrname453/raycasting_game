// initialize.c
#include "initialize.h"
#include <stdio.h>
#include "mixer.h"

// Initialize SDL, window, and renderer
int initialize_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if (mixer_init() != 0)
    {
        printf("Failed to initialize mixer\n");
        SDL_Quit();
        return 1;
    }

    // Create window
    *window = SDL_CreateWindow(
        "Raycasting Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (*window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    // Create renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

// Cleanup SDL and quit
void cleanup_sdl(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    mixer_cleanup();
    SDL_Quit();
}

// Cleanup all resources (map, player, shotgun)
void cleanup_resources(Player *player, Map *map, Shotgun *shotgun,Enemy *enemy)
{
    destroy_shotgun(shotgun);
    destroy_player(player);
    destroy_map(map);
    destroy_enemy(enemy);
}
