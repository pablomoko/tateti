#include <iostream>
#include <string>
#include "Tablero.h"
#include "Jugador.h"
#include "Carta.h"
#include "Pila.h"


class Juego {

private:

	Lista < Jugador * > * jugadores;
	Tablero * tablero;
	Pila < Carta * > * cartas;

	// clase interfaz ?  Para interactuar con usuario


public:
	/*
	 * Pre:	recibe las 3 dimensiones que tendra el tablero,
	 * la cantidad de fichas seguidas necesarias para ganar, cantidad de jugadores
	 * distinta de 0, y la cantidad de cartas en mano que se puede tener
	 *
	 * Post: valida y crea un nuevo juego. El juego se crea con un tablero de ancho x alto x profundo
	 * dimensiones, cantidadFichas que indica las necesarias para ganar, cantidadJugadores
	 * y cantidadCartas en mano que se puede tener
	 */
	Juego(unsigned int ancho, unsigned int alto, unsigned int profundo, unsigned int cantidadFichas, unsigned int cantidadJugadores, unsigned int cantidadCartas);
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


Juego::Juego(unsigned int ancho, unsigned int alto, unsigned int profundo, unsigned int cantidadFichas, unsigned int cantidadJugadores, unsigned int cantidadCartas) {

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
