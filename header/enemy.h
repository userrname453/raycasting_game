// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "player.h"
#define C_PI 3.14159265358979323846264338327950288

typedef struct {
    float x;
    float y;
    SDL_Texture* texture;
} Enemy;

Enemy* create_enemy(SDL_Renderer* renderer, Map* map);
void destroy_enemy(Enemy* enemy);
void draw_enemy(SDL_Renderer* renderer, Enemy* enemy, Player* player, Map* map);

#endif // ENEMY_H