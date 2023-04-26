#ifndef GAMELOGIC_HPP
#include "../headers/gamelogic.hpp"
#endif
#include <iostream>

int random(int min, int max){
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
}