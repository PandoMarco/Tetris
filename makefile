SOURCES=main.cpp
EXECUTABLE=main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ $(SOURCES) -lncurses -o $(EXECUTABLE)

