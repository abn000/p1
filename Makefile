OBJS = main.o Game.o Cell.o 
CFLAGS = -g -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

main : $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

main.o : main.cpp Game.hpp
	$(CC) $(CFLAGS) -c $<

Game.o : Game.cpp Game.hpp Cell.hpp
	$(CC) $(CFLAGS) -c $<

Cell.o : Cell.cpp Cell.hpp
	$(CC) $(CFLAGS) -c $<

clean :
	rm main $(OBJS)