#ifndef MIXER_H
#define MIXER_H

#include <SDL2/SDL_mixer.h>

// Initializes SDL_mixer and loads the shotgun sound
int mixer_init();

// Plays the shotgun sound
void play_shotgun_sound();

// Frees the sound and closes SDL_mixer
void mixer_cleanup();

#endif // MIXER_H
