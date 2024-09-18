#ifndef MIXER_H
#define MIXER_H

#include <SDL2/SDL_mixer.h>

int mixer_init(void);
void play_shotgun_sound(void);
void mixer_cleanup(void);

#endif /* MIXER_H */
