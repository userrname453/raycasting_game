#ifndef CHECK_WIN_H
#define CHECK_WIN_H

#include "player.h"
#include "enemy.h"
#include "map.h"
#include <SDL2/SDL.h>

int check_win(Player *player, const Uint8 *keys, Enemy *enemy, Map *map);
void display_win_texture(Player *player);

#endif // CHECK_WIN_H
