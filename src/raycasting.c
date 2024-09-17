#include "raycasting.h"
#include "draw_walls.h"
#include <math.h>
#include <SDL2/SDL_image.h> // To handle loading textures
#include <stdio.h> // For printf
#include "draw_sky.h"
#include "draw_floor.h"
// Add texture loading for wall1.png and wall2.png
void ray_cast(Player *player, Map *map, RaycastingResult *results)
{
    // Load textures
    SDL_Surface *wall1_surface = IMG_Load("resources/textures/wall1.png");
    SDL_Surface *wall2_surface = IMG_Load("resources/textures/wall2.png");

    if (!wall1_surface || !wall2_surface) {
        fprintf(stderr, "Failed to load wall textures! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    // Convert surfaces to textures
    SDL_Texture *wall1_texture = SDL_CreateTextureFromSurface(player->renderer, wall1_surface);
    SDL_Texture *wall2_texture = SDL_CreateTextureFromSurface(player->renderer, wall2_surface);

    // Free the surface as we now have textures
    SDL_FreeSurface(wall1_surface);
    SDL_FreeSurface(wall2_surface);

    if (!wall1_texture || !wall2_texture) {
        fprintf(stderr, "Failed to create wall textures! SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Draw sky and floor before raycasting
    draw_sky(player->renderer);   // Draw the sky
    draw_floor(player->renderer); // Draw the floor


    float ray_angle = player->angle - HALF_FOV + 0.0001;

    for (int ray = 0; ray < NUM_RAYS; ray++)
    {
        float sin_a = sinf(ray_angle);
        float cos_a = cosf(ray_angle);

        float x_hor, y_hor, depth_hor;
        calculate_horizontal_depth(player, map, sin_a, cos_a, &x_hor, &y_hor, &depth_hor);

        float x_vert, y_vert, depth_vert;
        calculate_vertical_depth(player, map, sin_a, cos_a, &x_vert, &y_vert, &depth_vert);

        // Depth and direction
        float depth = (depth_vert < depth_hor) ? depth_vert : depth_hor;
        int direction = (depth_vert < depth_hor) ? 1 : 0;

        // Offset calculation (for texturing)
        int offset = (depth_vert < depth_hor)
                     ?  fmod(y_vert, 100) 
                     :  fmod(x_hor, 100);

        // Remove fishbowl effect
        depth *= cos(player->angle - ray_angle);

        // Projection height
        float proj_height = SCREEN_DIST / (depth + 0.0001);

        // Store raycasting result
        results[ray] = (RaycastingResult){depth, proj_height, direction, offset};

        // Debugging output
        printf("Ray %d:\n", ray);
        printf("  Angle: %.2f\n", ray_angle);
        printf("  Depth: %.2f\n", depth);
        printf("  Projection Height: %.2f\n", proj_height);
        printf("  Direction: %d\n", direction);
        printf("  Offset: %d\n", offset);


        // Draw walls using textures
        if (direction == 1) {
            draw_wall_texture(player->renderer, wall1_texture, ray, proj_height, offset);
        } else {
            draw_wall_texture(player->renderer, wall2_texture, ray, proj_height, offset);
        }

        ray_angle += DELTA_ANGLE;
    }

    // Destroy textures after use
    SDL_DestroyTexture(wall1_texture);
    SDL_DestroyTexture(wall2_texture);
}
