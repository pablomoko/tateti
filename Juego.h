#ifndef JUEGO_H_
#define JUEGO_H_



#include <iostream>
#include <string>

#include "Tablero.h"
#include "Jugador.h"
#include "Carta.h"
#include "Cola.h"
#include "Interfaz.h"
#include "Constantes.h"



class Juego {

private:

	Lista < Jugador * > * jugadores;
    Cola < Carta * > * mazo;
    Jugador * ganador;
    Jugador * jugadorEnTurno;
    Tablero * tablero;
    Interfaz * interfaz;
    unsigned int cantidadMaximaCartas;
  	int jugadaAnterior[2][3];

public:
	/*
	 * Pre:	recibe las 3 dimensiones que tendra el tablero,
	 * la cantidad de fichas seguidas necesarias para ganar, cantidad de jugadores
	 * distinta de 0, y la cantidad de cartas en mano que se puede tener
	 * Post: crea un nuevo juego inicializando una Interfaz, un Jugador ganador nulo y una estructura
	 * para almacenar la jugadaAnterior. Luego pide por pantalla al usuario las dimensiones con las
	 * que desea crear el tablero, la cantidad de Jugadores y la cantidad maxima de cartas en mano
	 * con las que desea jugar
	 */
	Juego();


	/*
	 * Post: se libera memoria del heap usada para tablero, lista de jugadores, mazo de cartas
	 */
	~Juego();

	
	 /* Post: invoca a funciones de la interfaz con mensajes para el usuario
		 * 				realiza un ciclo while que se ejecuta mientras no haya ganador del Juego
		 * 				dentro del while  se muestra el tablero, se entrega una carta al jugador en turno,
		 *				opcionalmente se utiliza una carta, se pone/mueve una ficha,
		 *				y por ultimo se cambia el turno al siguiente jugador
		 *				Cuando se sale del while se muestra una vez mas el tablero, y el ganador del Juego
	*/
    void jugar();

private:

    /*
	 * Pre: recibe una matriz de enteros "jugadaActual" donde se cargara -1
	 *				ya que el historial de jugadas sera valido unas vez dispuestas todas las fichas
	 * Post: dentro de un ciclo while Pide coordenadas al usuario a traves de Interfaz, y en caso que el casillero
						indicando se encuentre disponible le cargara la ficha del jugador, y saldra del ciclo
	 *        caso contrario avisara al usuario mediante la Interfaz
	 *
    */
    void ponerFicha( int ** jugadaActual );


	/*
	 * Pre: recibe una matriz de enteros "jugadaActual" donde se cargara el movimiento realizado
	 * Post: dentro de un ciclo while Pide coordenadas de origen y destion al usuario a traves de Interfaz,
	 * 				y en caso que los casilleros indicandos  se encuentren disponibles realizara el movimiento
	 *				de la ficha del jugador y saldra del ciclo
	 * 				caso contrario avisara al usuario mediante la Interfaz
	*/
    void moverFicha( int ** jugadaActual );


	/*
	 * Post: pregunta al usuario si quiere utilizar una carta y cual quiere utilizar
	 *				en caso afirmativo usara la carta
	*/
    void usarCarta();


	/*
	 * Pre: recibe el número perteneciente a una carta del mazo (del 1 al 6?)
	 * Post: si el jugador no posee esa carta, no se hace nada
	 * el juego actúa según lo que haga la carta
	 */
	void activarCarta( funcion_t );


	/* Post: avanza una posicion en la lista de jugadores
	 * establece el nuevo jugadorEnTurno
	 */
 	void cambiarTurno();


	/*
	 * Post: entrega una carta al jugador actual si este no alcanzo el maximo de cartas
	 */
	void entregarCarta();



    /*
     * Pre: recibe el numero de jugador al que corresponde el nombre, por ejemplo:
     * Jugador 1: Tomas, Jugador 2: Miguel, etc
     * Post: pide por pantalla el nombre al jugador y devuelve una cadena con dicho nombre
     */
    std::string pedirNombre(int jugadorNumero);

    /*
     * Post: pide por pantalla la cantidad de jugadores que tendra el juego. Lanza excepcion
     * si se ingresa valor inválido
     */
    unsigned int pedirCantidadJugadores();

    /*
     * Post: pide por pantalla la cantidad de fichas que tendra cada Jugador. Lanza excepcion
     * si se ingresa valor inválido
     */
    unsigned int pedirCantidadFichas();

    /*
     * Post: devuelve un vector de 3 enteros
     */
    void pedirDimensionesTablero(int, int, unsigned int * dimensiones);


    /*
     * Post: devuelve un entero sin signo, cantidad maxima de cartas que podra tener
     * en su mano al mismo tiempo el jugador
     */
    unsigned int pedirCantidadCartasPorJugador();


    /*
     * Pre: recibe un entero que brinda el usuario
     * Post: devuelve el enumerativo correspondiente
     */
    funcion_t getFuncionalidad(unsigned int);


    /*
     * Post: pide por pantalla las coordenadas del casillero y chequea que sean validas
     * 		en caso de que no lo sean imprime por Interfaz un mensaje de ingreso invalido
     */
    Casillero * pedirCoordenadas();


    /*
	 * Pre: recibe un array de enteros que se cargara con con las coordenadas del usuario
	 * Post: pide por pantalla las coordenadas del casillero y chequea que sean validas
	 * 				en caso de que no lo sean imprime por Interfaz un mensaje de ingreso invalido
	 */
    Casillero * pedirCoordenadasB( int * coordenadas );


    /*
     * Post: avanza 2 jugadores en la lista, salteando al primero
     */
    void saltearSiguienteJugador();


    /*
     * Post: se deshace la jugada del jugador anterior al actual (la jugada realizada
     		por el jugadorEnTurno queda intacta)
     */
    void volverJugadaAtras();


    /*
    * Post: incrementa una ficha al jugadorEnTurno
   */
    void devolverFichaAJugadorAnterior();


	/*
	* Post: devuelve el jugador siguiente al jugadorEnTurno segun la lista de jugadores
	*/
    Jugador * obtenerJugadorSiguiente();


     /*
     * Pre: recibe el casillero donde se desea checkear si hay tateti o no
     * Post: devuelve en booleano si hay tateti o no en todas las direcciones del
     * Casillero recibido. Hay tateti cuando hay 3 casilleros adyacentes
     * con el mismo tipo de ficha
     */
    bool hayTateti(Casillero * casilleroOrigen);

};




#endif /* JUEGO_H_ */
