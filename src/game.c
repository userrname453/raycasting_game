#include "game.h"
#include "initialize.h"
#include "minimap.h"
#include "check_win.h"
#include "cleanup.h"

/**
 * handle_events - Handles SDL events
 * @state: Pointer to the GameState structure
 */
static void handle_events(GameState *state)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			state->running = 0;
	}
}

/**
 * update_game - Updates the game state
 * @state: Pointer to the GameState structure
 */
static void update_game(GameState *state)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (check_win(state->player, keys, state->enemy, state->map))
		state->win_condition_met = 1;

	if (!state->win_condition_met)
		player_update(state->player, keys);
}

/**
 * render_game - Renders the game to the screen
 * @state: Pointer to the GameState structure
 */
static void render_game(GameState *state)
{
	SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
	SDL_RenderClear(state->renderer);

	if (state->win_condition_met)
	{
		display_win_texture(state->player);
	}
	else
	{
		ray_cast(state->player, state->map, state->results);
		draw_enemy(state->renderer, state->enemy, state->player, state->map);
		render_shotgun(state->renderer, state->shotgun);
		draw_minimap(state->renderer, state->player, state->map);
	}

	SDL_RenderPresent(state->renderer);
}

/**
 * initialize_game - Initializes the game state
 * @state: Pointer to the GameState structure
 */
void initialize_game(GameState *state)
{
	if (!initialize_sdl(&state->window, &state->renderer))
		exit(1);

	state->map = create_map(state->renderer, "map.txt");
	state->shotgun = create_shotgun(state->renderer);
	state->player = create_player(state->renderer, state->map->mini_map,
								  state->shotgun);
	state->enemy = create_enemy(state->renderer, state->map);

	state->running = 1;
	state->win_condition_met = 0;
}

/**
 * run_game - Main game loop
 * @state: Pointer to the GameState structure
 */
void run_game(GameState *state)
{
	while (state->running)
	{
		handle_events(state);
		update_game(state);
		render_game(state);
		SDL_Delay(16);
	}
}
