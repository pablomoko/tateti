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
    Jugador * jugador = this->jugadores->obtenerCursor()->getDato();
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
            // Bloquear una ficha del siguiente jugador
            this->bloquearFicha(  )
            break;

        case 3:
            // A traves de la interfaz se pregunta qué casillero se quiere bloquear
            // Se llama a bloquear casillero
            break;

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

    if ( this->tablero->contarElementos() )
}


void Juego::jugar() {}

