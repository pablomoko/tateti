#include "Jugador.h"


Jugador::Jugador(std::string nombreJugador, Ficha * ficha, int cantidadFichas, std::string color){
    this->nombreJugador= nombreJugador;
    this->ficha = ficha;
    this->color = color;
    this->cantidadFichas = cantidadFichas;
    this->turnos = 1;
    this->cartas = new Lista<Carta *>;
}


Jugador::~Jugador() {
    this->cartas->iniciarCursor();
    while( this->cartas->avanzarCursor() ) {
        delete this->cartas->obtenerCursor();
    }
    delete this->cartas;
    delete this->ficha;
}


void Jugador::tomarCarta( Carta * nuevaCarta ) {

    this->cartas->altaFinal(nuevaCarta);
}


Carta * Jugador::usarCarta( funcion_t funcionalidad ) {

    Carta * carta;

    this->cartas->iniciarCursor();
    int indice = 1;

    while ( this->cartas->avanzarCursor() ) {

        carta = this->cartas->obtenerCursor();

        if ( carta->getFuncionalidad() == funcionalidad ) {
            this->cartas->remover(indice);
            return carta;
        }
        ++indice;
    }

    throw ("El jugador no posee la carta seleccionada");
}


Lista<Carta*> * Jugador::getCartas() {
    return this->cartas;
}


unsigned int Jugador::getCantidadFichas() const{

    return this->cantidadFichas;
}


void Jugador::incrementarCantidadFichas() {
    this->cantidadFichas++;
}


void Jugador::disminuirCantidadFichas(){

    this->cantidadFichas--;
}



// ------------------------------------
int Jugador::getNumeroDeTurnos() {

    return this->turnos;
}


void Jugador::saltear() {

    this->turnos = 0;
}


void Jugador::dobleTurno() {

    this->turnos = 2;
}


void Jugador::unTurno() {

    this->turnos = 1;
}
// ------------------------------------

Carta * Jugador::getUltimaCarta(){

    return this->cartas->bajaAlFinal();
}


unsigned int Jugador::getCantidadDeCartas() {

    return this->cartas->contarElementos();
}



Ficha * Jugador::getFicha() {

    return this->ficha;
}


std::string Jugador::getColor() {
    return this->color;
}