CC = g++
CXXFLAGS = -std=c++0x -m64 -Wall -c -fno-use-cxa-atexit -fPIC
LDFLAGS = -nostartfiles -nostdlib -m64 -shared

SOURCES=./src/AimTux.cpp ./src/draw.cpp
OBJECTS=./src/AimTux.o ./src/draw.o

OUT := aimtux-csgo.so

all: clean build

clean:
	rm -vf $(OBJECTS) $(OUT)

%.cpp: ../%.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -o "$@" "$<"

%.o: ../%.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -o "$@" "$<"

build: $(OBJECTS)
	$(CC) $(LDFLAGS) ./src/*.o -o $(OUT)
	rm  ./src/*.o
