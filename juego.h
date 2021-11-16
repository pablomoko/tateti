#include <iostream>
#include <string>
#include "Tablero.h"
#include "jugador.h"
#include "carta.h"
#include "pila.h"


class Juego {

private:

	Lista < Jugador * > * jugadores;
	Tablero * tablero;
	Pila < Carta * > * cartas;

	// clase interfaz ?  Para interactuar con usuario


public:
	/*
	 * Pre:		Recibe: 3 dimensiones, cant fichas p ganar, cant jugadores, cant cartas
	 * Post:
	 */
	Juego( int ancho, int alto, int profundo, int cantFichas, int cantJugadores, int cantCartas );
	// crear tablero
	// crear jugadores
	// crear cartas y repartir



	~Juego();
	// destruir tablero, lista de jugadores, y pila de cartas


	/*
	 * recibe coordenadas en el tablero; el jugador es el actual
	 */
	void ponerFicha();
	// con try - except

	/*
	 * recibe 2 coordenadas en el tablero; el jugador es el actual
	 */
	void moverFicha();
	// con try - except


	void activarCarta();

private:
    std::string pedirNombre( int );
    bool validarCantidadJugadores(int);
    bool validarCantidadCartas(int);
    bool validarDimensiones(int, int, int);

};

std::string pedirNombre( int jugadorNumero ) {
	std::string nombre[50];
	std::cout<<"Jugador "<<jugadorNumero<<" - Ingrese su nombre (max 10 caracteres) :";
	std::cin>>nombre;

	return nombre;
}


Juego::Juego( int ancho, int alto, int profundo, int cantFichas, int cantJugadores, int cantCartas ) {

    if (    !this->validarCantidadJugadores(cantJugadores) ||
            !this->validarCantidadCartas(cantCartas) ||
            !this->validarDimensiones(ancho, alto, profundo) ) {
        throw ( "Argumentos no validos" );
    }

	this->tablero = new Tablero( ancho, alto, profundo );

    this->cartas = new Pila<Carta *>;
    for ( int i=0; i < cantJugadores*cantCartas*100; ++i ) {
        unsigned int numeroDeCartaAleatorio = 3;            // CAMBIAR
        Carta * nuevaCarta = new Carta(numeroDeCartaAleatorio);
        this->cartas->push(nuevaCarta);
    }

	jugadores = new Lista < Jugador * >;
	for (int i = 0; i < cantJugadores; ++i) {
		std::string nombre = pedirNombre( i+1 );
		Ficha * ficha = new Ficha( 'A'+i );
		Jugador * nuevoJugador = new Jugador( nombre, ficha, cantFichas );

        for (int j = 0; j < cantCartas; ++j) {
            Carta * nuevaCarta = this->cartas->pop();
            nuevoJugador->tomarCarta(nuevaCarta);
        }
	}
}
