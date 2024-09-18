#include "minimap.h"
#include <math.h>

/**
 * draw_minimap - Draws the minimap on the screen
 * @renderer: SDL renderer
 * @player: Pointer to the Player
 * @map: Pointer to the Map
 */
void draw_minimap(SDL_Renderer *renderer, Player *player, Map *map)
{
	int tile_size = MINIMAP_SIZE / MAP_WIDTH;
	SDL_Rect bg_rect = {0, 0, MINIMAP_SIZE, MINIMAP_SIZE};
	SDL_Rect wall_rect, player_rect;
	int y, x, dir_x, dir_y;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderFillRect(renderer, &bg_rect);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (map->mini_map[y][x] == 1)
			{
				wall_rect = (SDL_Rect){x * tile_size, y * tile_size,
						       tile_size, tile_size};
				SDL_RenderFillRect(renderer, &wall_rect);
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	player_rect = (SDL_Rect){
		(int)(player->x / TILE_SIZE * tile_size) - 2,
		(int)(player->y / TILE_SIZE * tile_size) - 2,
		4, 4
	};
	SDL_RenderFillRect(renderer, &player_rect);

	dir_x = (int)(player->x / TILE_SIZE * tile_size + cosf(player->angle) * 10);
	dir_y = (int)(player->y / TILE_SIZE * tile_size + sinf(player->angle) * 10);
	SDL_RenderDrawLine(renderer, player_rect.x + 2, player_rect.y + 2,
	 dir_x, dir_y);
}
