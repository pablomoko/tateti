#ifndef JUGADOR_H_
#define JUGADOR_H_



#include <string>
#include "Ficha.h"
#include "Carta.h"
#include "Lista.h"


class Jugador {
friend class Ficha;

private:

    std::string nombreJugador;
    Ficha * ficha;
    std::string color;
    int cantidadFichas;
    Lista<Carta *> * cartas;
    int turnos;


public:

        /*
         * Pre: recibe un string, una ficha valida, y un entero mayor a cero
         * Post: inicializa atributos, toma memoria del heap para lista de cartas
         */
        Jugador(std::string nombreJugador, Ficha * ficha, int cantidadFichas, std::string color);


        /*
         * Pre: La lista de cartas fue creada en el heap
         * Post: se destruyen las cartas y la lista de cartas (libera memoria del heap)
         */
        ~Jugador();


        /*
         * Pre: recibe un puntero a instancia Carta
         * Post: almacena el puntero en la  lista cartas
         */
        void tomarCarta( Carta * );


        /*
         * Pre: recibe un numero entero entre 1 y 6 (numeros de cartas)
         * Post: retorna un puntero a Carta (sacada de la lista de cartas)
         */
        Carta * usarCarta( funcion_t );


        /*
         * Post: devuelve la lista de cartas del jugadors
         */
        Lista<Carta*> * getCartas();


        /*
         * Pre: -
         * Post: devuelve un entero mayor o igual a cero
         */
        unsigned int getCantidadFichas() const;


        /*
         * Post: agrega 1 ficha al jugador
         */
        void incrementarCantidadFichas();


        /*
         * Pre: -
         * Post: disminuye en 1 el valor CantidadFichas
         */
        void disminuirCantidadFichas();



        // ------------------------------------

        /*
          * Post: devuelve un entero represenativo del turno del jugador
          * 0: sin turno, 1: un solo turno, 2: doble turno
         */
        int getNumeroDeTurnos();


        /*
         * Post: establece el turno del jugador en 0
         */
        void saltear();


        /*
         * Post: establece el turno del jugador en 2
         */
        void dobleTurno();


        /*
         * Post: establece el turno del jugador en 1
         */
        void unTurno();

        // ------------------------------------



        /*
         * Pre: -
         * Post: devuelve un string con el nombre
         */
        std::string getNombre(){return this->nombreJugador;};


        /*
         * Pre: La lista de cartas no esta vacia (si esta vacia lanza error)
         * Post: Saca el ultimo elemento de la lista y lo devuelve
         *      (si la lista de cartas esta vacia lanza error)
         */
        Carta * getUltimaCarta();


        /*
         * Pre: -
         * Post: devuelve un entero mayor o igual a cero
         */
        unsigned int getCantidadDeCartas();


        /*
         * chequea si el jugador le quedan fichas para poner
         * quita la ficha de la lista
         * devuelve una ficha del jugador
        */
        Ficha * getFicha();


        /*
         */
        std::string getColor();
};



#endif /* JUGADOR_H_ */
