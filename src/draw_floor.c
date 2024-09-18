#include "draw_floor.h"
#include <SDL2/SDL.h>
#include "map.h"

/**
 * draw_floor - Draws the floor on the renderer
 * @renderer: The SDL renderer to draw on
 */
void draw_floor(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 161, 116, 110, 255);
	SDL_Rect floor = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};

	SDL_RenderFillRect(renderer, &floor);
}
