FLAGS = -lSDL2 -lSDL -lSDL_image -lSDL2_gfx -lSDL2_mixer
OBJECTS = graphics.o physicseng.o audio.o gamelogic.o game.o serialcommunication.o serialport.o

all: compileObjects compileMain copyDependencies fixPerms run clean

noard: compileObjects compileMain copyDependencies run clean

compileObjects:
	g++ -c -o physicseng.o ../src/physicseng.cpp
	g++ -c -o graphics.o ../src/graphics.cpp
	g++ -c -o audio.o ../src/audio.cpp
	g++ -c -o gamelogic.o ../src/gamelogic.cpp
	g++ -c -o game.o ../src/game.cpp
	g++ -c -o serialport.o ../src/SerialPort.cpp
	g++ -c -o serialcommunication.o ../src/serialcommunication.cpp

compileMain:
	g++ ../src/main.cpp $(OBJECTS) -o pong.x86_64 $(FLAGS)

copyDependencies:
	cp -r ../resources ../build/

fixPerms:
	sudo chmod a+rw /dev/ttyUSB0
	sudo chmod a+rw /dev/ttyUSB1
run:
	./pong.x86_64

clean:
	rm *.o