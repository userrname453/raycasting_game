// draw_floor.c
#include "draw_floor.h"
#include <SDL2/SDL.h>
#include "map.h"

void draw_floor(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Green floor color
    SDL_Rect floor = { 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
    SDL_RenderFillRect(renderer, &floor);
}
