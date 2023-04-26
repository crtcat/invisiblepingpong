#ifndef SERIALCOMMUNICATION_HPP
#define SERIALCOMMUNICATION_HPP
#endif
#ifndef BASEDATA_HPP
#include "../headers/basedata.hpp"
#endif
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <CppLinuxSerial/SerialPort.hpp>

class Arduino{
    public:
        axis readAcceleration(axis rollback);
        Arduino(std::string filename){
            serialFilename = filename;
        }
    private:
        void arduinoRead();
        std::string serialFilename;
        std::thread myThread;
        std::string readData[2];
	    std::string readBuffer;
        int timeoutctr = 0;
        bool threadRunning = false;
};

axis readAcceleration(Arduino ardinput, axis rollback);

