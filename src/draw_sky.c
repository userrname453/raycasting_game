// draw_sky.c
#include "draw_sky.h"
#include <SDL2/SDL.h>
#include "map.h"

void draw_sky(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue color
    SDL_Rect sky = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2 };
    SDL_RenderFillRect(renderer, &sky);
}
