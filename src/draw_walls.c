// draw_walls.c
#include "draw_walls.h"
#include <SDL2/SDL.h>
#include "map.h"
#include "raycasting.h"

void draw_wall_texture(SDL_Renderer *renderer, SDL_Texture *texture, int ray, float proj_height, int offset)
{
    // Define the source rectangle from the texture (using the offset)
    SDL_Rect src_rect;
    src_rect.x = offset;  // Offset determines the x position on the texture
    src_rect.y = 0;       // We want the full height of the texture
    src_rect.w = 1;       // 1 pixel width (we are drawing column by column)
    src_rect.h = 100;     // Full height of texture (assuming 100px)

    // Define the destination rectangle on the screen
    SDL_Rect dest_rect;
    dest_rect.x = ray * SCALE;
    dest_rect.y = (WINDOW_HEIGHT / 2) - proj_height / 2;
    dest_rect.w = SCALE;  // Width of the ray (scaled)
    dest_rect.h = proj_height;  // Height of the projected wall

    // Render the texture for this ray
    SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect);
}

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
