#include "draw_sky.h"
#include <SDL2/SDL.h>
#include "map.h"

/**
 * draw_sky - Draws the sky on the screen
 * @renderer: SDL renderer
 */
void draw_sky(SDL_Renderer *renderer)
{
	SDL_Rect sky;

	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); /* Sky blue color */
	sky.x = 0;
	sky.y = 0;
	sky.w = WINDOW_WIDTH;
	sky.h = WINDOW_HEIGHT / 2;
	SDL_RenderFillRect(renderer, &sky);
}
