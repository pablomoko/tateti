#include "Jugador.h"
using namespace std;


Jugador::Jugador(std::string nombreJugador,Ficha * fichas,int cantidadFichas){
    this->nombreJugador= nombreJugador;
    this->fichas = fichas;
    this->cantidadFichas = cantidadFichas;

    this->cartas = new Lista<Carta *>;
}


void Jugador::tomarCarta( Carta * nuevaCarta ) {

    this->cartas->altaFinal(nuevaCarta);
}


Carta * Jugador::usarCarta( unsigned int numeroCarta ) {

    int cantidadCartas = this->cartas->contarElementos();
    Carta * carta;

    for (int i = 0; i < cantidadCartas; ++i) {
        
        carta = this->cartas->obtener(i);
        if ( carta->getNumero() == numeroCarta ) {
            this->cartas->remover(i);
            return carta;
        }
    }

    throw ("El jugador no posee la carta seleccionada");
}


size_t Jugador::getCantidadFichas() const{

    return this->cantidadFichas;
}


void Jugador::disminuirCantidadFichas(){

    (this->cantidadFichas)--;
}




