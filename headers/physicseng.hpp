#ifndef PHYSICSENG_HPP
#define PHYSICSENG_HPP
#endif
#ifndef BASEDATA_HPP
#include "basedata.hpp"
#endif

void batBall(ball *ball, int direction, int speed, int x, int y, int z, int airtime);

void batBall(ball *ball, int direction, int speed, int z, int airtime);

void spawnBall(ball *ball, int x, int y, int z);

int findNewDirection(ball* ballEntity, int towardsPlayer, int spread);

void despawnBall(ball *ball);

void tickBallMovement(ball *ball);

void resetAnxiety();
