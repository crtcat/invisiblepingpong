#ifndef GAME_HPP
#define GAME_HPP
#endif
#ifndef BASEDATA_HPP
#include "basedata.hpp"
#endif

void gameSetup(ball *ballEntity);
void gameLoop(ball *ballEntity, SDL_Keycode eventInput);
void resetGame(ball *ballEntity);