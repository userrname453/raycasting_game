// src/game.c

#include <stdio.h>
#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void initializeSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simple Raycasting Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void cleanupSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void gameLoop(Player *player) {
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky color
        SDL_RenderClear(renderer);

        // Draw floor
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); // Grey floor
        SDL_Rect floorRect = {0, 300, 800, 300};
        SDL_RenderFillRect(renderer, &floorRect);

        // Draw walls
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow walls
        SDL_Rect wallRect = {300, 150, 50, 150};
        SDL_RenderFillRect(renderer, &wallRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Roughly 60 FPS
    }
}