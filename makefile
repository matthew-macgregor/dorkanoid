#~ 	g++ -Wall -g -std=c++11 -c main.cpp -o main.o
#~ 	g++ -o main.o -lsfml-graphics -lsfml-window -lsfml-system

CC=g++
CFLAGS=-Wall -g -std=c++11 -c
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SOURCES=src/main.cpp src/ball.cpp src/paddle.cpp src/brick.cpp src/util_rand.cpp src/sound_manager.cpp src/stage_one.cpp src/util_str.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dorkanoid

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@  $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f src/*.o

rebuild: clean all
