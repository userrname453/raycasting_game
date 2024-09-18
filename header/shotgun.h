#ifndef SHOTGUN_H
#define SHOTGUN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define SHOTGUN_FRAMES 6
#define ANIMATION_SPEED 100 /* milliseconds per frame */

/**
 * struct Shotgun - Represents the shotgun in the game
 * @frames: Array of texture frames for the shotgun
 * @current_frame: Current frame of the animation
 * @last_update: Timestamp of the last update
 * @is_firing: Flag indicating if the shotgun is firing
 */
typedef struct Shotgun
{
	SDL_Texture * frames[SHOTGUN_FRAMES];
	int current_frame;
	Uint32 last_update;
	int is_firing;
} Shotgun;

Shotgun *create_shotgun(SDL_Renderer *renderer);
void destroy_shotgun(Shotgun *shotgun);
void update_shotgun(Shotgun *shotgun);
void render_shotgun(SDL_Renderer *renderer, Shotgun *shotgun);
void start_shotgun_animation(Shotgun *shotgun);

#endif /* SHOTGUN_H */
