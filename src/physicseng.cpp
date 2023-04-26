#ifndef PHYSICSENG_HPP
#include "../headers/physicseng.hpp"
#endif
#ifndef BASEDATA_HPP
#include "../headers/basedata.hpp"
#endif
#ifndef PROPERTIES_HPP
#include "../headers/properties.hpp"
#endif
#ifndef GAMELOGIC_HPP
#include "../headers/gamelogic.hpp"
#endif
#ifndef AUDIO_HPP
#include "../headers/audio.hpp"
#endif
#include <cmath>
#include <iostream>

double anxiety = 1;

int findNewDirection(ball* ballEntity, int towardsPlayer, int spread){
    if(towardsPlayer == 2) return int(atan((double(ballEntity -> y) - 540 + double(spread * anxiety)) / (double(ballEntity -> x))) * 180/3.1415) + 180;
    return int(atan((double(ballEntity -> y) - 540 + double(spread * anxiety)) / (double(ballEntity -> x - 1920))) * 180/3.1415);
}

void resetAnxiety(){
    anxiety = 1;
}

void batBall(ball *ballEntity, int direction, int speed, int x, int y, int z, int airtime){
    if(ballEntity -> allowBatBallSound) {
        playPaddleBounceSFX();
        anxiety += 0.1;
    }
    ballEntity -> Direction = direction;
    ballEntity -> Speed = speed;
    ballEntity -> x = x;
    ballEntity -> y = y;
    ballEntity -> z = z;
    ballEntity -> ticksSinceBat = 0;
    ballEntity -> airtime = airtime;
}

void batBall(ball *ballEntity, int direction, int speed, int z, int airtime){
    if(ballEntity -> allowBatBallSound) {
        playPaddleBounceSFX();
        anxiety += 0.1;
    }
    ballEntity -> Direction = direction;
    ballEntity -> Speed = speed;
    ballEntity -> z = z;
    ballEntity -> ticksSinceBat = 0;
    ballEntity -> airtime = airtime;
}

void spawnBall(ball *ballEntity, int x, int y, int z){
    ballEntity -> exists = true;
    ballEntity -> x = x;
    ballEntity -> y = y;
    ballEntity -> z = z;
}

void despawnBall(ball *ballEntity){
    ballEntity -> exists = false;
    ballEntity -> x = 0;
    ballEntity -> y = 0;
    ballEntity -> z = 0;
    ballEntity -> Direction = 0;
    ballEntity -> Speed = 0;

}

void tickBallMovement(ball *ballEntity){
    if(ballEntity -> Speed == 0) return;
    if(!ballEntity -> exists) return;
    ballEntity -> ticksSinceBat++;
    // Movement
    ballEntity -> x += ballEntity -> Speed * cos(ballEntity -> Direction * M_PI / 180);  
    ballEntity -> y += ballEntity -> Speed * sin(ballEntity -> Direction * M_PI / 180);
    
    // Bounce
    ballEntity -> z = -1 * (pow(ballEntity -> ticksSinceBat % (ballEntity -> airtime), 2) - (ballEntity -> airtime) * (ballEntity -> ticksSinceBat % (ballEntity -> airtime)));
}