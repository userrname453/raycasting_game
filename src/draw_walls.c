// draw_walls.c
#include "draw_walls.h"
#include <SDL2/SDL.h>
#include "map.h"
#include "raycasting.h"

void draw_walls(SDL_Renderer *renderer, RaycastingResult *results) {
    for (int ray = 0; ray < NUM_RAYS; ray++) {
        SDL_SetRenderDrawColor(renderer, 
            results[ray].direction == 1 ? 211 : 169, 211, 211, SDL_ALPHA_OPAQUE); // Light grey for one side, Dark grey for the other

        SDL_Rect rect = {
            .x = ray * SCALE,
            .y = (WINDOW_HEIGHT / 2) - results[ray].proj_height / 2,
            .w = SCALE,
            .h = results[ray].proj_height
        };
        
        SDL_RenderFillRect(renderer, &rect);
    }
}
