#include <stdlib.h>
#include "player.h"
#include <stdio.h> 

// Function to create and initialize a Player
Player* create_player(SDL_Renderer* renderer, int mini_map[MAP_HEIGHT][MAP_WIDTH]) {
    Player* player = (Player*)malloc(sizeof(Player));
    if (!player) {
        fprintf(stderr, "Failed to allocate memory for Player.\n");
        exit(1);
    }
    player->x = PLAYER_POS_X;
    player->y = PLAYER_POS_Y;
    player->angle = PLAYER_ANGLE;
    player->renderer = renderer;

    // Copy the mini_map into player's mini_map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            player->mini_map[y][x] = mini_map[y][x];
        }
    }
    return player;
}

// Function to destroy a Player
void destroy_player(Player* player) {
    free(player);
}

// Check if a given position is within the world map
int check_wall(Player* player, int x, int y) {
    // Print the coordinates and corresponding map value for debugging
    
    // Check bounds and print the result of the bounds check
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return (player->mini_map[y][x] == 1);  // Wall if value is 1
    } else {
        return 0;  // Out of bounds is considered empty
    }
}

// Move the player and handle collisions
void player_movement(Player* player, const Uint8* keys) {
    float sin_a = sinf(player->angle);
    float cos_a = cosf(player->angle);
    float dx = 0, dy = 0;
    float speed = PLAYER_SPEED;  
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
    int new_x = (int)((player->x + dx) / TILE_SIZE);
    int new_y = (int)((player->y + dy) / TILE_SIZE);

    // Check if the new position is valid and update player position
    if (!check_wall(player, new_x, (int)(player->y / TILE_SIZE))) {
        player->x += dx;
    }
    if (!check_wall(player, (int)(player->x / TILE_SIZE), new_y)) {
        player->y += dy;
    }
}

// Draw the player on the screen
void player_draw(Player* player) {
    float end_x = player->x + TILE_SIZE * cosf(player->angle);
    float end_y = player->y + TILE_SIZE * sinf(player->angle);

    // Draw the line (if needed)
    SDL_SetRenderDrawColor(player->renderer, 255, 255, 0, 255); // Yellow color
    SDL_RenderDrawLine(player->renderer, player->x, player->y, end_x, end_y);

    // Draw the circle (player position)
    SDL_SetRenderDrawColor(player->renderer, 0, 255, 0, 255); // Green color
    SDL_RenderDrawPoint(player->renderer, player->x, player->y);
}

// Update the player (movement and drawing)
void player_update(Player* player) {
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    player_movement(player, keys);
    player_draw(player);
}
