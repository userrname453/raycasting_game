#include "shotgun.h"
#include <stdio.h>
#include "map.h"
#include "mixer.h"

/**
 * create_shotgun - Creates and initializes a Shotgun
 * @renderer: SDL renderer
 *
 * Return: Pointer to the created Shotgun or NULL if failed
 */
Shotgun *create_shotgun(SDL_Renderer *renderer)
{
	Shotgun *shotgun;
	char filename[64];
	int i;
	SDL_Surface *surface;

	shotgun = (Shotgun *)malloc(sizeof(Shotgun));
	if (!shotgun)
	{
		fprintf(stderr, "Failed to allocate memory for Shotgun.\n");
		return (NULL);
	}

	for (i = 0; i < SHOTGUN_FRAMES; i++)
	{
		snprintf(filename, sizeof(filename), "resources/shotgun/%d.png", i);
		surface = IMG_Load(filename);
		if (!surface)
		{
			fprintf(stderr, "Failed to load shotgun image %s! SDL_image Error: %s\n",
				filename, IMG_GetError());
			destroy_shotgun(shotgun);
			return (NULL);
		}
		shotgun->frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		if (!shotgun->frames[i])
		{
			fprintf(stderr, "Failed to create texture from %s! SDL Error: %s\n",
				filename, SDL_GetError());
			destroy_shotgun(shotgun);
			return (NULL);
		}
	}

	shotgun->current_frame = 0;
	shotgun->last_update = SDL_GetTicks();
	shotgun->is_firing = 0;

	return (shotgun);
}

/**
 * destroy_shotgun - Destroys a Shotgun
 * @shotgun: Pointer to the Shotgun to destroy
 */
void destroy_shotgun(Shotgun *shotgun)
{
	int i;

	if (shotgun)
	{
		for (i = 0; i < SHOTGUN_FRAMES; i++)
		{
			if (shotgun->frames[i])
				SDL_DestroyTexture(shotgun->frames[i]);
		}
		free(shotgun);
	}
}

/**
 * update_shotgun - Updates the shotgun animation
 * @shotgun: Pointer to the Shotgun
 */
void update_shotgun(Shotgun *shotgun)
{
	Uint32 current_time;

	if (shotgun->is_firing)
	{
		current_time = SDL_GetTicks();
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

/**
 * render_shotgun - Renders the shotgun on the screen
 * @renderer: SDL renderer
 * @shotgun: Pointer to the Shotgun
 */
void render_shotgun(SDL_Renderer *renderer, Shotgun *shotgun)
{
	SDL_Rect dst_rect = {0, 0, 0, 0};
	float scale = 0.5;

	SDL_QueryTexture(shotgun->frames[shotgun->current_frame], NULL, NULL,
			 &dst_rect.w, &dst_rect.h);

	dst_rect.w *= scale;
	dst_rect.h *= scale;
	dst_rect.x = (WINDOW_WIDTH - dst_rect.w) / 2;
	dst_rect.y = (WINDOW_HEIGHT - dst_rect.h);

	SDL_RenderCopy(renderer, shotgun->frames[shotgun->current_frame],
NULL, &dst_rect);
}

/**
 * start_shotgun_animation - Starts the shotgun firing animation
 * @shotgun: Pointer to the Shotgun
 */
void start_shotgun_animation(Shotgun *shotgun)
{
	if (!shotgun->is_firing)
	{
		play_shotgun_sound();
		shotgun->is_firing = 1;
		shotgun->current_frame = 1;
		shotgun->last_update = SDL_GetTicks();
	}
}
