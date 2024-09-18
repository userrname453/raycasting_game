#include "mixer.h"
#include <stdio.h>

static Mix_Chunk *shotgun_sound;

/**
 * mixer_init - Initializes SDL_mixer and loads sounds
 *
 * Return: 0 on success, -1 on failure
 */
int mixer_init(void)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
		       Mix_GetError());
		return (-1);
	}

	shotgun_sound = Mix_LoadWAV("resources/sounds/shotgun.wav");
	if (shotgun_sound == NULL)
	{
		printf("Failed to load shotgun sound! SDL_mixer Error: %s\n",
		       Mix_GetError());
		return (-1);
	}

	return (0);
}

/**
 * play_shotgun_sound - Plays the shotgun sound effect
 */
void play_shotgun_sound(void)
{
	if (shotgun_sound != NULL)
		Mix_PlayChannel(-1, shotgun_sound, 0);
}

/**
 * mixer_cleanup - Frees sound resources and closes SDL_mixer
 */
void mixer_cleanup(void)
{
	if (shotgun_sound != NULL)
	{
		Mix_FreeChunk(shotgun_sound);
		shotgun_sound = NULL;
	}
	Mix_CloseAudio();
}
