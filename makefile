CC = g++
CXXFLAGS =-fPIC -std=c++14 -g -shared -ldl

SOURCES = $(shell find src/ -type f -name '*.cpp')
OBJECTS = $(patsubst src/%.cpp, src/%.o, $(SOURCES))
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
	rm $(OBJECTS)
