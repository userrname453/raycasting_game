#include "initialize.h"
#include <stdio.h>
#include "mixer.h"

/**
 * create_window - Creates an SDL window
 * @window: Pointer to SDL_Window pointer
 *
 * Return: 1 on success, 0 on failure
 */
static int create_window(SDL_Window **window)
{
	*window = SDL_CreateWindow("Raycasting Game", SDL_WINDOWPOS_UNDEFINED,
				    SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
				    WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (*window == NULL)
	{
		fprintf(stderr, "Window could not be created! SDL_Error: %s\n",
			SDL_GetError());
		return (0);
	}
	return (1);
}

/**
 * create_renderer - Creates an SDL renderer
 * @renderer: Pointer to SDL_Renderer pointer
 * @window: SDL_Window to create renderer for
 *
 * Return: 1 on success, 0 on failure
 */
static int create_renderer(SDL_Renderer **renderer, SDL_Window *window)
{
	*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		fprintf(stderr, "Renderer could not be created! SDL_Error: %s\n",
			SDL_GetError());
		SDL_DestroyWindow(window);
		return (0);
	}
	return (1);
}

/**
 * initialize_sdl - Initializes SDL, window, and renderer
 * @window: Pointer to SDL_Window pointer
 * @renderer: Pointer to SDL_Renderer pointer
 *
 * Return: 1 on success, 0 on failure
 */
int initialize_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
	int imgFlags = IMG_INIT_PNG;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (0);
	}

	if (mixer_init() != 0)
	{
		printf("Failed to initialize mixer\n");
		SDL_Quit();
		return (0);
	}

	if (!create_window(window))
	{
		SDL_Quit();
		return (0);
	}

	if (!create_renderer(renderer, *window))
	{
		SDL_Quit();
		return (0);
	}

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n",
			IMG_GetError());
		SDL_DestroyRenderer(*renderer);
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return (0);
	}

	return (1);
}




