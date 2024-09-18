#include "check_win.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "enemy.h"
#include "map.h"

/**
 * check_win - Check if the player has won
 * @player: Pointer to the player structure
 * @keys: Array of keyboard states
 * @enemy: Pointer to the enemy structure
 * @map: Pointer to the map structure
 *
 * Return: 1 if the player has won, 0 otherwise
 */
int check_win(Player *player, const Uint8 *keys, Enemy *enemy, Map *map)
{
	if (keys[SDL_SCANCODE_SPACE] &&
	    is_player_facing_enemy(player, enemy->x, enemy->y) &&
	    !check_wall_intersection(map, player->x, player->y, enemy->x, enemy->y))
	{
		return (1);
	}
	return (0);
}

/**
 * display_win_texture - Display the win texture on the screen
 * @player: Pointer to the player structure
 */
void display_win_texture(Player *player)
{
	SDL_Surface *win_surface;
	SDL_Texture *win_texture;
	SDL_Rect dest_rect;

	win_surface = IMG_Load("resources/win.png");
	if (win_surface)
	{
		win_texture = SDL_CreateTextureFromSurface(player->renderer, win_surface);
		SDL_FreeSurface(win_surface);

		dest_rect.x = 0;
		dest_rect.y = 0;
		dest_rect.w = WINDOW_WIDTH;
		dest_rect.h = WINDOW_HEIGHT;
		SDL_RenderCopy(player->renderer, win_texture, NULL, &dest_rect);
		SDL_DestroyTexture(win_texture);
	}
	else
	{
		fprintf(stderr, "Failed to load win texture! SDL_image Error: %s\n",
			IMG_GetError());
	}
}
