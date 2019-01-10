OBJS = main.o 
CFLAGS = -g -Wall
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++

main : main.o
	$(CC) -o $@ $< $(LIBS)

main.o : main.cpp
	$(CC) $(CFLAGS) -c $<