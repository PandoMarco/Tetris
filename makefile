SOURCES=main.cpp menu.cpp punteggio.cpp visualizza_classifica.cpp
EXECUTABLE=tetris

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ $(SOURCES) -lncurses -o $(EXECUTABLE)

