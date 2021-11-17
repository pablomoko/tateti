#include "Juego.h"

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
