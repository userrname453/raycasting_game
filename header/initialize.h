#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <SDL2/SDL.h>

#define WIDTH 1600
#define HEIGHT 900

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDLContext;

SDLContext initialize_sdl(void);
void cleanup_sdl(SDLContext *context);

#endif // INITIALIZE_H