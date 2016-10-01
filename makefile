CC = g++
CXXFLAGS =-fPIC -std=c++14 -g -shared -ldl

SOURCES := ./src/UI/component.cpp ./src/AimTux.cpp ./src/draw.cpp ./src/netvarmanager.cpp ./src/offsets.cpp ./src/hooker.cpp ./src/aimbot.cpp ./src/esp.cpp ./src/bhop.cpp ./src/spammer.cpp ./src/autostrafe.cpp ./src/entity.cpp ./src/antiaim.cpp ./src/triggerbot.cpp ./src/skinchanger.cpp ./src/math.cpp ./src/UI/window.cpp ./src/UI/panel.cpp
OBJECTS:= ./src/UI/component.o ./src/AimTux.o ./src/draw.o ./src/netvarmanager.o ./src/offsets.o ./src/hooker.o ./src/aimbot.o ./src/esp.o ./src/bhop.o ./src/spammer.o ./src/autostrafe.o ./src/entity.o ./src/antiaim.o ./src/triggerbot.o ./src/skinchanger.cpp ./src/math.cpp ./src/UI/window.o ./src/UI/panel.o
OUT := aimtux-csgo.so

all: clean build

clean:
	rm -vf $(OBJECTS) $(OUT)

%.cpp: ../%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<" -ldl

%.o: ../%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<" -ldl

build: $(OBJECTS)
	$(CC) $(CXXFLAGS) -static-libgcc -L. -o $(OUT) $(OBJECTS) -ldl
	rm  ./src/*.o
	rm  ./src/UI/*.o
