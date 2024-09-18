#include "check_win.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

int check_win(Player *player, const Uint8 *keys, Enemy *enemy) {
    if (keys[SDL_SCANCODE_SPACE] && is_player_facing_enemy(player, enemy->x, enemy->y)) {
        return 1; // Return 1 to indicate a win condition
    }
    return 0; // Return 0 if the win condition is not met
}

void display_win_texture(Player *player) {
    // Load and render win.png
    SDL_Surface *win_surface = IMG_Load("resources/win.png");
    if (win_surface) {
        SDL_Texture *win_texture = SDL_CreateTextureFromSurface(player->renderer, win_surface);
        SDL_FreeSurface(win_surface);

        // Render the win texture
        SDL_Rect dest_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderCopy(player->renderer, win_texture, NULL, &dest_rect);
        SDL_DestroyTexture(win_texture);
        printf("win ");
    } else {
        fprintf(stderr, "Failed to load win texture! SDL_image Error: %s\n", IMG_GetError());
    }
}
