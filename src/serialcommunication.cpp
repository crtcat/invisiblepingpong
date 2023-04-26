#ifndef SERIALCOMMUNICATION_HPP
#include "../headers/serialcommunication.hpp"
#endif
#ifndef BASEDATA_HPP
#include "../headers/basedata.hpp"
#endif

using namespace mn::CppLinuxSerial;

void Arduino::arduinoRead(){

	SerialPort serialPort(serialFilename, BaudRate::B_9600, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
	std::cout << "Opened Serial Port: " << serialFilename << std::endl;

	serialPort.SetTimeout(10);
	serialPort.Open();

	threadRunning = true;

	while(true){
		serialPort.Read(readBuffer);
		if(!readBuffer.empty()){
			readData[0] = readBuffer;
			readData[1] = serialFilename;
			readBuffer.clear();
			timeoutctr = 0;
		} else{
			timeoutctr++;
		}
	}
}

axis Arduino::readAcceleration(axis rollback){
	if(!threadRunning){
		myThread = std::thread(&Arduino::arduinoRead, this);
		myThread.detach();
	}
	if(readData[0].empty()) return rollback;
	if(readData[1] != serialFilename) return rollback;
	std::cout << "Read: " << readData[0] << " from " << readData[1] << " in " << serialFilename << std::endl;
	int pickedAxis = -1;
	int startPos = -1;
	int endPos = -1;
	axis axisData;
	for(int i = 0; i < readData[0].length(); i++){
		switch(readData[0][i]){
			case 'X':
				pickedAxis = 0;
				startPos = i;
				break;
			case 'Y':
				pickedAxis = 1;
				startPos = i;
				break;
			case 'Z':
				pickedAxis = 2;
				startPos = i;
				break;
			case ';':
				endPos = i;
				break;
		}
		if(startPos != -1 && endPos != -1){
			try{
				switch(pickedAxis){
					case 0:
						axisData.x = std::stof(readData[0].substr(startPos + 1, endPos - startPos - 1));
						break;
					case 1:
						axisData.y = std::stof(readData[0].substr(startPos + 1, endPos - startPos - 1));
						break;
					case 2:
						axisData.z = std::stof(readData[0].substr(startPos + 1, endPos - startPos - 1));
						break;
				}
				pickedAxis = -1;
				startPos = -1;
				endPos = -1;
			} catch(std::invalid_argument e){}
		}
		if(axisData.x != 0 && axisData.y != 0 && axisData.z != 0){
			readData[0].clear();
			readData[1].clear();
			break;
		}
	}
	if(axisData.x == 0 || axisData.y == 0 || axisData.z == 0){
		return axis{0, 0, 0};
	}
	return axisData;
}
    


