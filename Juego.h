#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Jugador.h"
#include "Carta.h"
#include "Cola.h"
#include "Interfaz.h"

srand( time(NULL) );

class Juego {

private:

	Lista < Jugador * > * jugadores; // lista circular de jugadores
	Jugador * jugadorEnTurno; // sirve para luego saber quien fue el ultimo que jugo, quien gano
	Tablero * tablero;
	Cola < Carta * > * mazo;
    Interfaz * interfaz;


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


	/* Pre: -
	 * Post: se libera memoria del heap usada para tablero, lista de jugadores, mazo de 
     *  		cartas
	 */
	~Juego();


	/*
	 * recibe coordenadas en el tablero; el jugador es el actual
	 */
	void ponerFicha();
	// con try - except

	void jugar();

	/*
	 * recibe 2 coordenadas en el tablero; el jugador es el actual
	 */
	void moverFicha();
	// con try - except


	/* Pre: recibe el número perteneciente a una carta del mazo (del 1 al 6?)
	 * Post: si el jugador no posee esa carta, no se hace nada
	 * el juego actúa según lo que haga la carta
	 */
	void activarCarta( unsigned int );


	/* avanza una posicion en la lista de jugadores
	 * establece el nuevo jugadorEnTurno
	 */
 	void cambiarTurno();


	/* itera la lista de jugadores, para cada uno
	 * 		retira una carta del mazo
	 *    agrega una carta al jugador (llama a tomarCarta)
	 * post: disminuyen cartas del mazo, cada jugador toma una carta
	 */
	void repartirCartas();


	// recibe las coordenadas de la ficha que se movio/coloco para chequear el tateti ahi
	bool chequearTateti(/* coordenadas de la ficha movida */);


private:

    std::string pedirNombre( int );
    bool validarCantidadJugadores(int);
    bool validarCantidadCartas(int);
    bool validarDimensiones(int, int, int);

    bool validarPosicionEnElTablero( int, int, int );

    void bloquearSiguienteJugador();

    void bloquearFicha( int, int, int );

    void bloquearCasillero( int, int, int );

};
