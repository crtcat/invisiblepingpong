#ifndef WINDOW_HPP
#define WINDOW_HPP
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);