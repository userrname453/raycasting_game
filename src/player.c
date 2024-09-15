#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> // Include math.h for sinf and cosf

// Function to create and initialize a Player
Player* create_player(SDL_Renderer* renderer, Uint8* world_map) {
    Player* player = (Player*)malloc(sizeof(Player));
    if (!player) {
        fprintf(stderr, "Failed to allocate memory for Player.\n");
        exit(1);
    }
    player->x = PLAYER_POS_X;
    player->y = PLAYER_POS_Y;
    player->angle = PLAYER_ANGLE;
    player->renderer = renderer;
    player->world_map = world_map;
    return player;
}

// Function to destroy a Player
void destroy_player(Player* player) {
    free(player);
}

// Check if a given position is within the world map
int check_wall(Player* player, int x, int y) {
    // Placeholder for wall check logic; update according to your map representation
    return (player->world_map[y * 10 + x] == 0);  // Update based on map width
}

// Move the player and handle collisions
void player_movement(Player* player, const Uint8* keys) {
    float sin_a = sinf(player->angle);
    float cos_a = cosf(player->angle);
    float dx = 0, dy = 0;
    float speed = PLAYER_SPEED;  // Fixed speed, no delta_time needed
    float speed_sin = speed * sin_a;
    float speed_cos = speed * cos_a;

    if (keys[SDL_SCANCODE_W]) {
        dx += speed_cos;
        dy += speed_sin;
    }
    if (keys[SDL_SCANCODE_S]) {
        dx -= speed_cos;
        dy -= speed_sin;
    }
    if (keys[SDL_SCANCODE_A]) {
        dx += speed_sin;
        dy -= speed_cos;
    }
    if (keys[SDL_SCANCODE_D]) {
        dx -= speed_sin;
        dy += speed_cos;
    }

    player_check_wall_collision(player, dx, dy);

    if (keys[SDL_SCANCODE_LEFT]) {
        player->angle -= PLAYER_ROT_SPEED;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        player->angle += PLAYER_ROT_SPEED;
    }
}

// Check wall collision and update player position
void player_check_wall_collision(Player* player, float dx, float dy) {
    if (check_wall(player, (int)(player->x + dx), (int)player->y)) {
        player->x += dx;
    }
    if (check_wall(player, (int)player->x, (int)(player->y + dy))) {
        player->y += dy;
    }
}

// Draw the player on the screen
void player_draw(Player* player) {
    float end_x = player->x + 100 * cosf(player->angle);
    float end_y = player->y  + 100 * sinf(player->angle);

    // Draw the line (if needed)
    SDL_SetRenderDrawColor(player->renderer, 255, 255, 0, 255); // Yellow color
    SDL_RenderDrawLine(player->renderer, player->x , player->y , end_x, end_y);

    // Draw the circle (player position)
    SDL_SetRenderDrawColor(player->renderer, 255, 0, 0, 255); // Red color
    SDL_Rect rect = { (int)(player->x  - 2), (int)(player->y  - 2), 4, 4 };
    SDL_RenderFillRect(player->renderer, &rect); // Draw filled rectangle for the player
}

// Update the player (movement and drawing)
void player_update(Player* player) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    player_movement(player, keys);
    player_draw(player);
}
