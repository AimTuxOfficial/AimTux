CC = g++
CXXFLAGS = -std=c++0x -m64 -Wall -c -fno-use-cxa-atexit -fPIC
LDFLAGS = -nostartfiles -nostdlib -m64 -shared

SOURCES=./src/AimTux.cpp
OBJECTS=$(SOURCES:.cpp=.o)

OUT := libchameleon-csgo.so

all: clean build

clean:
	rm -vf $(OBJECTS) $(OUT)

%.o: ../%.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -o "$@" "$<"

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUT) $(LDFLAGS)
	rm  ./src/*.o
