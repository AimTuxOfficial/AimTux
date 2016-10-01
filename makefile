CC = g++
CXXFLAGS =-fPIC -std=c++14 -g -shared -ldl

SOURCES :=./src/AimTux.cpp ./src/draw.cpp ./src/netvarmanager.cpp ./src/offsets.cpp ./src/hooker.cpp ./src/aimbot.cpp ./src/settings.cpp ./src/esp.cpp ./src/bhop.cpp ./src/spammer.cpp ./src/autostrafe.cpp ./src/entity.cpp ./src/antiaim.cpp ./src/triggerbot.cpp ./src/UI/window.cpp ./src/UI/panel.cpp ./src/math.cpp
OBJECTS:= ./src/AimTux.o ./src/draw.o ./src/netvarmanager.o ./src/offsets.o ./src/hooker.o ./src/aimbot.o ./src/settings.o ./src/esp.o ./src/bhop.o ./src/spammer.o ./src/autostrafe.o ./src/entity.o ./src/antiaim.o ./src/triggerbot.o ./src/UI/window.o ./src/UI/panel.o ./src/math.o
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
