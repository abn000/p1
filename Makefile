BIN = bin
OBJS = $(BIN)/main.o $(BIN)/Game.o $(BIN)/Cell.o 
CFLAGS = -g -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

$(BIN)/main : $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(BIN)/main.o : main.cpp Game.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/Game.o : Game.cpp Game.hpp Cell.hpp
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/Cell.o : Cell.cpp Cell.hpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm $(BIN)/main $(OBJS)