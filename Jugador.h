#ifndef _JUGADOR_H_INCLUDED_
#define _JUGADOR_H_INCLUDED_

#include <iostream>
#include "Ficha.h"
#include "Carta.h"
#include "Lista.h"


class Jugador {
friend class Ficha;

private:

    std::string nombreJugador;
    Ficha * ficha; // deberia ser una lista ??
    int cantidadFichas;
    Lista<Carta *> * cartas;
    Estado estado;


public:

        /*
         * Pre: recibe un string, una ficha valida, y un entero mayor a cero
         * Post: inicializa atributos, toma memoria del heap para lista de cartas
         */
        Jugador(std::string nombreJugador, Ficha * fichas, int cantidadFichas);


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
        Carta * usarCarta( unsigned  int );


        /*
         * Pre: -
         * Post: devuelve un entero mayor o igual a cero
         */
        unsigned int getCantidadFichas() const;


        /*
         * Pre:
         * Post:
         */
        void incrementarCantidadFichas();


        /*
         * Pre: -
         * Post: disminuye en 1 el valor CantidadFichas
         */
        void disminuirCantidadFichas();


        /*
         * Pre: -
         * Post: devuelve True si estado=bloqueado
         */
        bool estaBloqueado();


        /*
         * Pre: -
         * Post: cambia el estado a bloqueado
         */
        void bloquear();


        /*
         * Pre: -
         * Post: cambia el estado a desbloqueado
         */
        void desbloquear();


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
        Carta * getCarta();


        /*
         * Pre: -
         * Post: devuelve un entero mayor o igual a cero
         */
        unsigned int getCantidadDeCartas();


        /*
         * Pre: recibe dos coordenadas pertenecientes al tablero. Las primeras indican cual
         * ficha mover y las segundas hacia donde. El movimiento debe ser adyacente
         *
         * Post: intercambia la ficha del casillero ubicado en la primer coordenada con el de la segunda
         * si las coordenadas son inválidas lanza una excepcion
         */
        void moverFicha(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int x2, unsigned int y2, unsigned int z2);

        /*
         * chequea si el jugador le quedan fichas para poner
         * quita la ficha de la lista
         * devuelve una ficha del jugador
        */
        Ficha * getFicha();
};

#endif
