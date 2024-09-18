#include "cleanup.h"
#include <SDL2/SDL_image.h>
#include "mixer.h"

/**
 * cleanup_sdl - Cleans up SDL resources
 * @window: SDL_Window to destroy
 * @renderer: SDL_Renderer to destroy
 */
void cleanup_sdl(SDL_Window *window, SDL_Renderer *renderer)
{
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
IMG_Quit();
mixer_cleanup();
SDL_Quit();
}

/**
 * cleanup_resources - Cleans up game resources
 * @player: Player to destroy
 * @map: Map to destroy
 * @shotgun: Shotgun to destroy
 * @enemy: Enemy to destroy
 */
void cleanup_resources(Player *player, Map *map, Shotgun *shotgun,
Enemy *enemy)
{
destroy_shotgun(shotgun);
destroy_player(player);
destroy_map(map);
destroy_enemy(enemy);
}

/**
 * cleanup_all - Cleans up all resources and SDL
 * @state: Pointer to the GameState structure
 */
void cleanup_all(GameState *state)
{
cleanup_resources(state->player, state->map, state->shotgun, state->enemy);
cleanup_sdl(state->window, state->renderer);
}
