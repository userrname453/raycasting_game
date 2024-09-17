#ifndef DRAW_WALLS_H
#define DRAW_WALLS_H

#include <SDL2/SDL.h>

void draw_wall_texture(SDL_Renderer *renderer, SDL_Texture *texture, int ray, float proj_height, int offset);

#endif // DRAW_WALLS_H
