#include "Jugador.h"
using namespace std;


Jugador::Jugador(std::string nombreJugador,Ficha * ficha,int cantidadFichas){
    this->nombreJugador= nombreJugador;
    this->ficha = ficha;
    this->cantidadFichas = cantidadFichas;
    this->estado = desbloqueado;

    this->cartas = new Lista<Carta *>;
}


Jugador::~Jugador() {

    this->cartas->iniciarCursor();
    while( this->cartas->avanzarCursor() ) {
        delete this->cartas->obtenerCursor();
    }

    delete this->cartas;
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


unsigned int Jugador::getCantidadFichas() const{

    return this->cantidadFichas;
}


void Jugador::disminuirCantidadFichas(){

    (this->cantidadFichas)--;
}


bool Jugador::estaBloqueado() {

    return ( this->estado == BLOQUEADO );
}


void Jugador::bloquear() {

    this->estado = BLOQUEADO;
}


void Jugador::desbloquear() {

    this->estado = DESBLOQUEADO;
}


Carta * Jugador::getCarta(){

    return this->cartas->bajaAlFinal();
}


unsigned int Jugador::getCantidadDeCartas() {

    return this->cartas->contarElementos();
}


void Jugador::moverFicha(Casillero * casilleroOrigen, Casillero * casilleroDestino) {

    // validacion
    // if(! sePuedeMover(casilleroOrigen, casilleroDestino)) {
    //   throw ""
    // }

    casilleroDestino->setFicha( casilleroOrigen->quitarFicha() );

/*
    //Valida si las coordenadas ingresadas son válidas
    if(x1 > casilleros->contarElementos() ||
       x2 > casilleros->contarElementos() ||
       y1 > casilleros->obtener(1)->contarElementos() ||  //La posicion escogida es arbitraria, ya que el tablero es cuadrado
       y2 > casilleros->obtener(1)->contarElementos()){
        throw "Una de las coordenadas ingresadas esta fuera de los limites del tablero";
    }

    //Intercambia fichas, se podría implementar usando anterior y siguiente?
    Ficha * ficha1 = casilleros->obtener(x1)->obtener(y1)->obtener(z1)->getFicha();
    Ficha * ficha2 = casilleros->obtener(x2)->obtener(y2)->obtener(z2)->getFicha();
    casilleros->obtener(x2)->obtener(y2)->obtener(z1)->setFicha(ficha1);
    casilleros->obtener(x1)->obtener(y1)->obtener(z1)->setFicha(ficha2);
*/
}
