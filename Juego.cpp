#include "Juego.h"

//PASAR A LA INTERFAZ
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

    this->mazo = new Cola<Carta *>;
    for ( int i=0; i < cantJugadores*cantCartas*100; ++i ) {
        unsigned int numeroDeCartaAleatorio = rand() % 6;
        Carta * nuevaCarta = cartasDisponibles->obtener(numeroDeCartaAleatorio);
        this->mazo->push(nuevaCarta);
    }

    jugadores = new Lista < Jugador * >;
    for (int i = 0; i < cantJugadores; ++i) {
        std::string nombre = pedirNombre( i+1 );
        Ficha * ficha = new Ficha( 'A'+i );
        Jugador * nuevoJugador = new Jugador( nombre, ficha, cantFichas );
    }
}



Juego::~Juego() {
    delete this->tablero;
    delete this->jugadores;
    delete this->mazo;
}


void Juego::cambiarTurno() {
  // inicia el cursor en nulo
  this->jugadores->iniciarCursor();
  // itero la lista en busca del jugador en turno
  for(int i = 0; i < this->jugadores->contarElementos(); i++) {
    // apunto al primer jugador
    this->jugadores->avanzarCursor();
    if( this->jugadorEnTurno == jugadores->obtenerCursor() ) {
      // si es el jugador en turno, avanzo uno mas (si llega al final empiezo de nuevo)
      
      if ( !(jugadores->avanzarCursor() ) ) {
        this->jugadores->iniciarCursor();
        this->jugadores->avanzarCursor();
      }

      if ( jugadores->obtenerCursor()->estaBloqueado() ) {
        //si el sig jugador esta bloqueado, avanzo uno mas, y lo desbloqueo para la proxima
        jugadores->obtenerCursor()->desbloquear();
        jugadores->avanzarCursor();
      }

      // establezco el nuevo jugador en turno
      this->jugadorEnTurno = jugadores->obtenerCursor();
    }
  }
  // con esta solucion se itera la lista cada vez que se cambia el turno.
  // no es gran problema porque la cantidad de jugadores va a ser 2,3,4,5... a lo sumo 10
}


Jugador Juego::*obtenerJugador(){
    this->jugadores->iniciarCursor();
    for(int i = 0; i < this->cantidadJugadores; i++){
        if(this->jugadorEnTurno->getNombre() == this->jugadores->obtenerCursor()->getNombre()){
            this->jugadores->avanzarCursor();
            return this->jugadores->obtenerCursor();
        }
        this->avanzarCursor();
    }
    return NULL;
}


void Juego::repartirCartas() {
  // inicia el cursor en nulo
  this->jugadores->iniciarCursor();
  // apunto al primer nodo que apunta a jugador
  this->jugadores->avanzarCursor();
  // itero la lista de jugadores
  for( int i = 0; i < this->cantidadJugadores; i++ ) {
    // saco carta del mazo
    Carta * nuevaCarta = this->mazo->pop();
    // entrego carta al jugador i
    Jugador * jugador = this->jugadores->obtenerCursor();
    jugador->tomarCarta(nuevaCarta);
    // avanzo al siguiente nodo que apunta al sig jugador
    this->jugadores->avanzarCursor();
  }
}


void Juago::activarCarta( unsigned int numeroDeCarta ) {

    try {
        Carta * carta = this->jugadorEnTurno->usarCarta( numeroDeCarta );
        // Si el jugador no tiene esa carta, tira error
    }
    catch (...) {
        throw (" ");
    }

    this->cartas->push(carta); // agrego la carta usada al final del mazo

    switch numeroDeCarta {

        case 1:
            // Hacer perder un turno al siguiente jugador
            this->bloquearFicha();
            break;

        case 2:
            // Pedir coordenadas
            // Bloquear la ficha del tablero
            try {
                this->bloquearFicha( 1,1,1 )
            }
            catch (...) {
                // Informar Posicion no válida
            }
            break;

        case 3:
            // Pedir coordenadas
            // Bloquear ese casillero
            try {
                this->bloquearCasillero( 1,1,1 )
            }
            catch (...) {
                // Informar Posicion no válida
            }
            break;
            
        case 4:
            //Cuando tengamos la funcion jugar, se haria uso de dicha funcion.  "this->jugar()";
            break;
        case 5:
            try{
                  Jugador *jugadorElegido = this->obtenerJugador(string nombre);
                  Carta *carta = jugadorElegido->getCarta();
                  this->jugadorEnTurno->tomarCarta(carta);
            }
            catch(...){
                //O no existe jugador con ese nombre o no tiene cartas en su mano
    }
}


void Juego::bloquearSiguienteJugador() {

    this->jugadores->iniciarCursor();
    bool listo = false;

    while( (this->jugadores->avanzarCursor()) && (!listo) ) {
        
        if ( this->jugadorEnTurno == this->jugadores->obtenerCursor() ) {
            this->jugadores->avanzarCursor();
            this->jugadores->obtenerCursor()->bloquear();
            listo = true;
        }
    }
}


void Juego::bloquearFicha( int ancho, int alto, int profundo ) {

    if ( ! (this->validarPosicion( ancho, alto, profundo )) ) {
        throw("Posicion no válida para el tablero actual");
    }

    try {
        this->tablero->obtener(ancho)->obtener(alto)->obtener(profundo)->getCasillero()->getFicha()->bloquear();
    }
    catch (...) {
        throw("No hay ficha en esa posicion")
    }
}


void Juego::bloquearCasillero( int ancho, int alto, int profundo ) {

    if ( ! (this->validarPosicion( ancho, alto, profundo )) ) {
        throw("Posicion no válida para el tablero actual");
    }

    this->tablero->obtener(ancho)->obtener(alto)->obtener(profundo)->getCasillero()->bloquear();
}


bool Juego::validarPosicionEnElTablero( int ancho, int alto, int profundo ) {

    if ( ancho<0 || ancho>=*(this->tablero->getDimensiones()) ||
         alto<0  || alto>=*(this->tablero->getDimensiones()+1)) ||
         profundo<0 || profundo>=*(this->tablero->getDimensiones()+2) {

            return false;
         }

    return true;
}


bool Juego::validarDimensiones( int x,  int y,  int z ) {

    if ( x<0 || y<0 || z<0 ) {
        return false;
    }

    return true;
}


bool Juego::validarCantidadJugadores( int x ) {

    if ( x<0 ) {
        return false;
    }

    return true;
}


bool Juego::validarCantidadCartas( int x ) {

    if ( x<0 ) {
        return false;
    }

    return true;
}



void Juego::jugar() {}

