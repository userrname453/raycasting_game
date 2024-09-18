#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"

#define C_PI 3.14159265358979323846264338327950288

/**
 * struct Enemy - Represents an enemy in the game
 * @x: x-coordinate of the enemy
 * @y: y-coordinate of the enemy
 * @texture: SDL texture for the enemy
 */
typedef struct Enemy
{
	float x;
	float y;
	SDL_Texture *texture;
} Enemy;

Enemy *create_enemy(SDL_Renderer *renderer, Map *map);
void destroy_enemy(Enemy *enemy);
void draw_enemy(SDL_Renderer *renderer, Enemy *enemy, Player *player,
Map *map);
int check_wall_intersection(Map *map, float x1, float y1, float x2, float y2);

#endif /* ENEMY_H */
