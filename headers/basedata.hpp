#ifndef BASEDATA_HPP
#define BASEDATA_HPP
#endif
#include <SDL2/SDL.h>

struct player{
    int paddleSpeed;
};

struct ball{
    bool exists;
    int Speed;
    int Direction;
    int x, y, z;
    int ticksSinceBat = 0; // Ticks since batting
    int airtime; // Ticks of airtime   
    int bounceInterval = 0; // Bounce interval, used if bounceOnWalls is true
    int playerThatLastBatted = 0;
    bool allowBatBallSound = 1;
};

struct axis{
    float x, y, z;
};