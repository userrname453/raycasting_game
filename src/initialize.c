#include "initialize.h"
#include <stdio.h>

SDLContext initialize_sdl(void)
{
    SDLContext context = {NULL, NULL};

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return context;
    }

    // Create window
    context.window = SDL_CreateWindow(
        "Map Display",           // Window title
        SDL_WINDOWPOS_UNDEFINED, // Initial x position
        SDL_WINDOWPOS_UNDEFINED, // Initial y position
        WIDTH,            // Width, in pixels
        HEIGHT,           // Height, in pixels
        SDL_WINDOW_SHOWN         // Window flags
    );
    if (context.window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return context;
    }

    // Create renderer
    context.renderer = SDL_CreateRenderer(
        context.window,          // Window
        -1,                      // Renderer index
        SDL_RENDERER_ACCELERATED // Renderer flags
    );
    if (context.renderer == NULL)
    {
        fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(context.window);
        SDL_Quit();
        return context;
    }

    return context;
}

void cleanup_sdl(SDLContext *context)
{
    if (context->renderer)
    {
        SDL_DestroyRenderer(context->renderer);
    }
    if (context->window)
    {
        SDL_DestroyWindow(context->window);
    }
    SDL_Quit();
}