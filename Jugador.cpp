#include "Jugador.h"
using namespace std;


Jugador::Jugador(std::string nombreJugador,Ficha * ficha,int cantidadFichas){
    this->nombreJugador= nombreJugador;
    this->ficha = ficha;
    this->cantidadFichas = cantidadFichas;
    //this->estado = desbloqueado;
    this->turnos = 1;
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


Carta * Jugador::usarCarta( funcion_t funcnionalidad ) {

    int cantidadCartas = this->cartas->contarElementos();
    Carta * carta;

    for (int i = 0; i < cantidadCartas; ++i) {

        carta = this->cartas->obtener(i);
        if ( carta->getFuncionalidad() == funcnionalidad ) {
            this->cartas->remover(i);
            return carta;
        }
    }

    throw ("El jugador no posee la carta seleccionada");
}


unsigned int Jugador::getCantidadFichas() const{

    return this->cantidadFichas;
}


void Jugador::incrementarCantidadFichas() {
    this->cantidadFichas++;
}


void Jugador::disminuirCantidadFichas(){

    (this->cantidadFichas)--;
}

/*
    bool Jugador::estaBloqueado() {

        return ( this->estado == JUGADOR_BLOQUEADO );
    }


    void Jugador::bloquear() {

        this->estado = JUGADOR_BLOQUEADO;
    }


    void Jugador::desbloquear() {

        this->estado = JUGANDO;
    }


    void Jugador::repetirTurno() {

        this->estado = DOBLE_TURNO;
    }


    bool Jugador::repiteTurno() {

        return this->estado == DOBLE_TURNO;
    }


    void Jugador::finDobleTurno() {

    }

*/

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

Ficha * Jugador::getFicha() {
    //return this->fichas->bajaAlFinal()
    return this->ficha;
}
