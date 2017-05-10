SOURCES=main.cpp player.cpp gameController.cpp grid.cpp 
EXECUTABLE = RadioTime


OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)
CFLAGS=-c -MMD -MP -Wall --std=c++11 -g
LFLAGS=--std=c++11 -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-network -lz -ltmx-loader -lpugi -g
CC=g++

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(DEPENDS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

-include $(DEPENDS)
