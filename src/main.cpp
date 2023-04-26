#ifndef ENTITIES_HPP
#include "../headers/entities.hpp"
#endif
#ifndef GRAPHICS_HPP
#include "../headers/graphics.hpp"
#endif
#ifndef AUDIO_HPP
#include "../headers/audio.hpp"
#endif
#ifndef GAME_HPP
#include "../headers/game.hpp"
#endif
#ifndef SERIALCOMMUNICATION_HPP
#include "../headers/serialcommunication.hpp"
#endif

bool shouldQuit = false;

int main(){
    gameSetup(&ballEntity);
    SDL_Event event;
    while(!shouldQuit){
        SDL_Keycode input = pullInput(event);
        shouldQuit = tickGameGraphics(input);
        gameLoop(&ballEntity, input);
        updateScreen();
    }
    endAudio();
    destroySDL();
    SDL_Quit();
}