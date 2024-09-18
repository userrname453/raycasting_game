#include "draw_walls.h"
#include <SDL2/SDL.h>
#include "map.h"
#include "raycasting.h"

/**
 * draw_wall_texture - Draws a textured wall column
 * @renderer: SDL renderer
 * @texture: Wall texture
 * @ray: Current ray number
 * @proj_height: Projected wall height
 * @offset: Texture offset
 */
void draw_wall_texture(SDL_Renderer *renderer, SDL_Texture *texture,
		       int ray, float proj_height, int offset)
{
	SDL_Rect src_rect, dest_rect;

	src_rect.x = offset;
	src_rect.y = 0;
	src_rect.w = 1;
	src_rect.h = 100;

	dest_rect.x = ray * SCALE;
	dest_rect.y = (WINDOW_HEIGHT / 2) - proj_height / 2;
	dest_rect.w = SCALE;
	dest_rect.h = proj_height;

	SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}

/**
 * draw_walls - Draws all wall columns
 * @renderer: SDL renderer
 * @results: Array of raycasting results
 */
void draw_walls(SDL_Renderer *renderer, RaycastingResult *results)
{
	int ray;
	SDL_Rect rect;

	for (ray = 0; ray < NUM_RAYS; ray++)
	{
		SDL_SetRenderDrawColor(renderer,
				       results[ray].direction == 1 ? 211 : 169,
				       211, 211, SDL_ALPHA_OPAQUE);

		rect.x = ray * SCALE;
		rect.y = (WINDOW_HEIGHT / 2) - results[ray].proj_height / 2;
		rect.w = SCALE;
		rect.h = results[ray].proj_height;

		SDL_RenderFillRect(renderer, &rect);
	}
}
