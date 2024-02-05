SOURCES=menu.cpp tetris.cpp tetramino.cpp visualizza_classifica.cpp
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ $(SOURCES) -lncurses -o $(EXECUTABLE)
