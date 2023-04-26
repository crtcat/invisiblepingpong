#ifndef GRAPHICS_HPP
#include "../headers/graphics.hpp"
#endif
#ifndef WINDOW_HPP
#include "../headers/window.hpp"
#endif
#ifndef BASEDATA_HPP
#include "../headers/basedata.hpp"
#endif
#include <iostream>

void drawGameArea(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 960, 0, 960, 1080);
}

void initializeGraphics(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

SDL_Keycode pullInput(SDL_Event event){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            return event.key.keysym.sym;
        }
        if(event.type == SDL_QUIT){
            return SDLK_ESCAPE;
        }
    }
    return 0;
}

bool tickGameGraphics(SDL_Keycode inputEvent){
    if(inputEvent == SDLK_ESCAPE){
        return true;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawGameArea(renderer);
    return false;
}

void updateScreen(){
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/60);
}

void destroySDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* getRenderer(){
    return renderer;
}