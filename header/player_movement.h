#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <math.h>
#include "map.h"
#include "shotgun.h"

#define PLAYER_POS_X 150
#define PLAYER_POS_Y 150
#define PLAYER_ANGLE 0
#define PLAYER_SPEED 2.5
#define PLAYER_ROT_SPEED 0.035
#define C_PI 3.14159265358979323846264338327950288
#define TILE_SIZE 100

/**
 * struct Player - Represents the player in the game
 * @x: x-coordinate of the player
 * @y: y-coordinate of the player
 * @angle: Angle of the player's view
 * @renderer: SDL renderer for rendering graphics
 * @mini_map: 2D array representing the mini-map
 * @shotgun: Pointer to the player's shotgun
 */
typedef struct Player
{
float x;
float y;
float angle;
SDL_Renderer *renderer;
int mini_map[MAP_HEIGHT][MAP_WIDTH];
Shotgun *shotgun;
} Player;

/**
 * create_player - Creates a new player instance.
 * @renderer: Pointer to the SDL renderer.
 * @mini_map: 2D array representing the mini-map.
 * @shotgun: Pointer to the player's shotgun.
 *
 * Return: Pointer to the newly created Player instance.
 */
Player *create_player(SDL_Renderer *renderer,
int mini_map[MAP_HEIGHT][MAP_WIDTH], Shotgun *shotgun);

/**
 * destroy_player - Frees resources associated with the player.
 * @player: Pointer to the Player to be destroyed.
 */
void destroy_player(Player *player);

/**
 * player_update - Updates the player's position based on input keys.
 * @player: Pointer to the Player.
 * @keys: Keyboard state.
 */
void player_update(Player *player, const Uint8 *keys);

/**
 * is_player_facing_enemy - Checks if the player is facing a specific enemy.
 * @player: Pointer to the Player.
 * @ex: x-coordinate of the enemy.
 * @ey: y-coordinate of the enemy.
 *
 * Return: 1 if the player is facing the enemy, 0 otherwise.
 */
int is_player_facing_enemy(Player *player, float ex, float ey);

/**
 * player_check_wall_collision - Checks for wall
 * collisions and updates position.
 * @player: Pointer to the Player.
 * @dx: Change in x-coordinate.
 * @dy: Change in y-coordinate.
 */
void player_check_wall_collision(Player *player, float dx, float dy);

#endif /* PLAYER_H */
