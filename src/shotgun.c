#include "shotgun.h"
#include <stdio.h>
#include "map.h"

Shotgun *create_shotgun(SDL_Renderer *renderer)
{
    Shotgun *shotgun = (Shotgun *)malloc(sizeof(Shotgun));
    if (!shotgun)
    {
        fprintf(stderr, "Failed to allocate memory for Shotgun.\n");
        return NULL;
    }

    char filename[64];
    for (int i = 0; i < SHOTGUN_FRAMES; i++)
    {
        snprintf(filename, sizeof(filename), "resources/shotgun/%d.png", i);
        SDL_Surface *surface = IMG_Load(filename);
        if (!surface)
        {
            fprintf(stderr, "Failed to load shotgun image %s! SDL_image Error: %s\n", filename, IMG_GetError());
            destroy_shotgun(shotgun);
            return NULL;
        }
        shotgun->frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!shotgun->frames[i])
        {
            fprintf(stderr, "Failed to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
            destroy_shotgun(shotgun);
            return NULL;
        }
    }

    shotgun->current_frame = 0;
    shotgun->last_update = SDL_GetTicks();
    shotgun->is_firing = 0;

    return shotgun;
}

void destroy_shotgun(Shotgun *shotgun)
{
    if (shotgun)
    {
        for (int i = 0; i < SHOTGUN_FRAMES; i++)
        {
            if (shotgun->frames[i])
            {
                SDL_DestroyTexture(shotgun->frames[i]);
            }
        }
        free(shotgun);
    }
}

void update_shotgun(Shotgun *shotgun)
{
    if (shotgun->is_firing)
    {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - shotgun->last_update > ANIMATION_SPEED)
        {
            shotgun->current_frame++;
            if (shotgun->current_frame >= SHOTGUN_FRAMES)
            {
                shotgun->current_frame = 0;
                shotgun->is_firing = 0;
            }
            shotgun->last_update = current_time;
        }
    }
}

void render_shotgun(SDL_Renderer *renderer, Shotgun *shotgun)
{
    SDL_Rect dst_rect = {0, 0, 0, 0};
    SDL_QueryTexture(shotgun->frames[shotgun->current_frame], NULL, NULL, &dst_rect.w, &dst_rect.h);

    // Scale the shotgun image to fit the bottom center of the screen
    float scale = 0.5; // Adjust this value to change the size of the shotgun
    dst_rect.w *= scale;
    dst_rect.h *= scale;
    dst_rect.x = (WINDOW_WIDTH - dst_rect.w) / 2;
    dst_rect.y = (WINDOW_HEIGHT - dst_rect.h);

    SDL_RenderCopy(renderer, shotgun->frames[shotgun->current_frame], NULL, &dst_rect);
}

void start_shotgun_animation(Shotgun *shotgun)
{
    if (!shotgun->is_firing)
    {
        shotgun->is_firing = 1;
        shotgun->current_frame = 1; // Start from the first firing frame
        shotgun->last_update = SDL_GetTicks();
    }
}