CC = g++
CXXFLAGS = -std=c++0x -m64 -Wall -c -fno-use-cxa-atexit -fPIC
LDFLAGS = -nostartfiles -nostdlib -m64 -shared

SOURCES=./chameleon/Chameleon.cc
OBJECTS=$(SOURCES:.cc=.o)

OUT := libchameleon-csgo.so

all: clean build

clean:
	rm -vf $(OBJECTS) $(OUT)

%.o: ../%.cc
	$(CC) $(CFLAGS) $(CFLAGS) -o "$@" "$<"

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUT) $(LDFLAGS)
