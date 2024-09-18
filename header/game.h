#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "shotgun.h"
#include "enemy.h"

/**
 * struct GameState - Represents the state of the game
 * @window: Pointer to the SDL_Window
 * @renderer: Pointer to the SDL_Renderer
 * @map: Pointer to the Map structure
 * @shotgun: Pointer to the Shotgun structure
 * @player: Pointer to the Player structure
 * @enemy: Pointer to the Enemy structure
 * @results: Array of Raycasting results
 * @running: Flag indicating if the game is running
 * @win_condition_met: Flag indicating if the win condition is met
 *
 * Description: This structure holds all the necessary components
 * and state variables for the game.
 */
typedef struct GameState
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	Map *map;
	Shotgun *shotgun;
	Player *player;
	Enemy *enemy;
	RaycastingResult results[NUM_RAYS];
	int running;
	int win_condition_met;
} GameState;

void initialize_game(GameState *state);
void run_game(GameState *state);

#endif /* GAME_H */
