#include "jugador.h"
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

    int indice = 3;
    //int indice = this->cartas->elementoPertenece(numeroCarta);
    if ( indice == -1 ) {
        throw ("El jugador no posee la carta que se quiere usar");
    }
    else {
        Carta * carta = this->cartas->obtener(indice);
        this->cartas->remover(indice);
        return  carta;
    }
}


size_t Jugador::getCantidadFichas() const{
    return this->cantidadFichas;
}


void Jugador::disminuirCantidadFichas(){
    (this->cantidadFichas)--;
}




