#ifndef GAME_HPP
#include "../headers/game.hpp"
#endif
#ifndef PHYSICSENG_HPP
#include "../headers/physicseng.hpp"
#endif
#ifndef GRAPHICS_HPP
#include "../headers/graphics.hpp"
#endif
#ifndef AUDIO_HPP
#include "../headers/audio.hpp"
#endif
#ifndef GAMELOGIC_HPP
#include "../headers/gamelogic.hpp"
#endif
#ifndef SERIALCOMMUNICATION_HPP
#include "../headers/serialcommunication.hpp"
#endif
#include <iostream>
#include <chrono>
#include <thread>

axis accelerometer1;
axis accelerometer2;
Arduino arduino1("/dev/ttyUSB0");
Arduino arduino2("/dev/ttyUSB1");

bool preparedAccelerometers = false;
int score[2] = {0, 0};
int servingPlayer = 1;
bool manualRestartRequired = false;

void resetGame(ball *ballEntity, int servingPlayerInput){
    if(servingPlayerInput == 0) servingPlayerInput = 1;
    servingPlayer = servingPlayerInput;
    playSFX("resources/voices/words/player " + std::to_string(servingPlayer) + " serve.wav");
    despawnBall(ballEntity);
    resetAnxiety();
    if(servingPlayer == 1) spawnBall(ballEntity, 1920, 540, 0);
    if(servingPlayer == 2) spawnBall(ballEntity, 0, 540, 0);
}

void announcePoints(ball *ballEntity){
    if(score[0]==8){
        playSFX("resources/voices/words/player 1 wins.wav");
        sleep(2);
        playSFX("resources/voices/words/restart.wav");
        despawnBall(ballEntity);
        manualRestartRequired = true;
        return;
    }
    if(score[1]==8){
        playSFX("resources/voices/words/player 2 wins.wav");
        sleep(2);
        playSFX("resources/voices/words/restart.wav");
        despawnBall(ballEntity);
        manualRestartRequired = true;
        return;
    }
    playSFX("resources/voices/numbers/" + std::to_string(score[0]) + ".wav");
    sleep(1);
    playSFX("resources/voices/words/to.wav");
    sleep(1);
    playSFX("resources/voices/numbers/" + std::to_string(score[1]) + ".wav");
    sleep(1);
    if(score[0]==7||score[1]==7) {
        playSFX("resources/voices/words/match point.wav");
        sleep(2);
    } 
}

void resultGame(ball *ballEntity, int player, int reason, bool awardPoints){
    if(player - 1 != 0 && player - 1 != 1) {
        playSFX("resources/voices/words/reserv.wav");
        sleep(1);
        return;
    }
    score[player - 1]++;
    switch(reason){
        case 1: // Ball crossed the players side
            playSFX("resources/voices/words/foul ball.wav");
            sleep(1);
            announcePoints(ballEntity);
            if(!manualRestartRequired) resetGame(ballEntity, 2 - (player - 1));
            break;
        case 2: // Ball went to the side of the table (Foul)
            playSFX("resources/voices/words/miss.wav");
            sleep(1);
            announcePoints(ballEntity);
            if(!manualRestartRequired) resetGame(ballEntity, 2 - (player - 1));
            break;
    }
    
}

void gameSetup(ball *ballEntity){
    initializeGraphics();
    initAudio();
    playSFX("resources/voices/words/player " + std::to_string(servingPlayer) + " serve.wav");
    if(servingPlayer == 1) spawnBall(ballEntity, 1920, 540, 0);
    if(servingPlayer == 2) spawnBall(ballEntity, 0, 540, 0);
}

void gameLoop(ball *ballEntity, SDL_Keycode eventInput){
    tickBallMovement(ballEntity);
    
    if(preparedAccelerometers == false){
        arduino2.readAcceleration(accelerometer2);
        sleep(2);
        arduino1.readAcceleration(accelerometer1);
        sleep(2);
        preparedAccelerometers = true;
    }

    if(ballEntity -> x < 960){
        accelerometer2 = arduino2.readAcceleration(accelerometer2);
    }
    if(ballEntity -> x > 960){
        accelerometer1 = arduino1.readAcceleration(accelerometer1);
    }

    if(ballEntity -> exists){
        filledCircleRGBA(getRenderer(), ballEntity -> x, ballEntity -> y, 10, 255, 255, 255, 255);
        if(ballEntity -> x > 460 && ballEntity -> x < 500) {
            playTableBounceSFX();
            ballEntity -> allowBatBallSound = true;
        }
        if(ballEntity -> x > 1420 && ballEntity -> x < 1460) {
            playTableBounceSFX();
            ballEntity -> allowBatBallSound = true;
        }
    }

    if(ballEntity -> y < 0 || ballEntity -> y > 1080){
        resultGame(ballEntity, 2 - (ballEntity -> playerThatLastBatted - 1), 1, true);
    }
    
    if(ballEntity -> x < -380 || ballEntity -> x > 2300){
        resultGame(ballEntity, ballEntity->playerThatLastBatted, 2, true);
    }

    // Player 1 Controls
    if(ballEntity -> x > 1400 && ballEntity -> x < 2300){
        if(eventInput==SDLK_DOWN || accelerometer1.z < -15) {
            batBall(ballEntity, findNewDirection(ballEntity, 2, (ballEntity -> x - 1920) * 2), 20, 0, 35);
            ballEntity->playerThatLastBatted = 1;
            ballEntity->allowBatBallSound = false;
        }
    }

    // Player 2 Controls
    if(ballEntity -> x > -380 && ballEntity -> x < 520 || servingPlayer == 2){
        if(eventInput==SDLK_s || accelerometer2.z < -15 && ballEntity->playerThatLastBatted!=2) {
            batBall(ballEntity, findNewDirection(ballEntity, 1, (ballEntity -> x) * 2), 20, 0, 35);
            ballEntity->playerThatLastBatted = 2;
            ballEntity->allowBatBallSound = false;
        }
    }

    if(eventInput==SDLK_r) {
        score[0] = 0;
        score[1] = 0;
        resetGame(ballEntity, 1);
    }
}

