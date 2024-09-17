#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SHOTGUN_FRAMES 6
#define ANIMATION_SPEED 100 // milliseconds per frame

typedef struct {
    SDL_Texture* frames[SHOTGUN_FRAMES];
    int current_frame;
    Uint32 last_update;
    int is_firing;
} Shotgun;

Shotgun* create_shotgun(SDL_Renderer* renderer);
void destroy_shotgun(Shotgun* shotgun);
void update_shotgun(Shotgun* shotgun);
void render_shotgun(SDL_Renderer* renderer, Shotgun* shotgun);
void start_shotgun_animation(Shotgun* shotgun);

#endif // SHOTGUN_H