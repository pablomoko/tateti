CFLAGS=-g -pedantic -Wall
CC=g++

all: tp2 clear

#Make Main

tp2: ficha.o casillero.o jugador.o main.o
	$(CC) $(CFLAGS) -o tp2  casillero.o  jugador.o  ficha.o main.o 

#Make Obj

main.o: main.cpp 
	$(CC) $(CFLAGS) -o main.o  -c main.cpp

casillero.o: casillero.cpp casillero.h 
	$(CC) $(CFLAGS) -o casillero.o  -c casillero.cpp

jugador.o: jugador.cpp  jugador.h 
	$(CC) $(CFLAGS) -o jugador.o  -c jugador.cpp

ficha.o: ficha.cpp  ficha.h 
	$(CC) $(CFLAGS) -o ficha.o  -c ficha.cpp

#Make Clear

clear:
	rm *.o

install:
	cp tp2 ../tp2

leak_test:
	valgrind --leak-check=full ./tp2