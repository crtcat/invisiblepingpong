#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void drawGameArea(SDL_Renderer *renderer);

void initializeGraphics();

bool tickGameGraphics(SDL_Keycode SDL_TextInputEvent);

SDL_Keycode pullInput(SDL_Event event);

void updateScreen();

void destroySDL();

SDL_Renderer* getRenderer();