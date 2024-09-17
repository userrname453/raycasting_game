#include "mixer.h"
#include <stdio.h>

static Mix_Chunk *shotgun_sound = NULL;

int mixer_init() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    // Load the shotgun sound
    shotgun_sound = Mix_LoadWAV("resources/sounds/shotgun.wav");
    if (shotgun_sound == NULL) {
        printf("Failed to load shotgun sound! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }

    return 0;
}

void play_shotgun_sound() {
    if (shotgun_sound != NULL) {
        Mix_PlayChannel(-1, shotgun_sound, 0);
    }
}

void mixer_cleanup() {
    // Free the sound and close SDL_mixer
    if (shotgun_sound != NULL) {
        Mix_FreeChunk(shotgun_sound);
        shotgun_sound = NULL;
    }
    Mix_CloseAudio();
}
