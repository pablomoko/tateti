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
    Ficha * fichas;
    int cantidadFichas;
    Lista<Carta *> * cartas;
    Estado estado;


public:
        Jugador(std::string nombreJugador, Ficha * fichas, int cantidadFichas);

        ~Jugador();

        void tomarCarta( Carta * );

        Carta * usarCarta( unsigned  int );

        unsigned int getCantidadFichas() const;

        void disminuirCantidadFichas();

        bool estaBloqueado();

        void bloquear();

        void desbloquear();

        std::string getNombre(){return this->nombreJugador;};

        Carta *getCarta();

        unsigned int getCantidadDeCartas();

        /*
         * Pre: recibe dos coordenadas pertenecientes al tablero. Las primeras indican cual
         * ficha mover y las segundas hacia donde. El movimiento debe ser adyacente
         *
         * Post: intercambia la ficha del casillero ubicado en la primer coordenada con el de la segunda
         * si las coordenadas son inválidas lanza una excepcion
         */
        void moverFicha(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int x2, unsigned int y2, unsigned int z2);
};

#endif
