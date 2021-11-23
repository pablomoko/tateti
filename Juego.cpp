#include "Juego.h"

/*PASAR A LA INTERFAZ
std::string pedirNombre( int jugadorNumero ) {
    std::string nombre[50];
    std::cout<<"Jugador "<<jugadorNumero<<" - Ingrese su nombre (max 10 caracteres) :";
    std::cin>>nombre;

    return nombre;
}
*/
Juego::Juego() {

    this->interfaz = new Interfaz();

    unsigned int cantidadJugadores = pedirCantidadJugadores();
    unsigned int cantidadFichas = pedirCantidadFichas();

    this->jugadores = new Lista < Jugador * >;
    for (unsigned int i = 0; i < cantidadJugadores; i++) {
        std::string nombre = pedirNombre(i + 1);
        Ficha * ficha = new Ficha('A' + i);
        Jugador * nuevoJugador = new Jugador(nombre, ficha, cantidadFichas);
        this->jugadores->altaFinal(nuevoJugador);
    }
    this->jugadorEnTurno = this->jugadores->obtener(1);

    unsigned int dimensiones[3] = pedirDimensionesTablero();
    this->tablero = new Tablero(dimensiones[0], dimensiones[1], dimensiones[2]);

    this->cantidadMaximaCartas = pedirCantidadCartasPorJugador();
    this->mazo = new Cola<Carta *>;
    for (int i = 0; i < cantidadJugadores * this->cantidadMaximaCartas * 100; i++) {
        // mejorar implementacion
        unsigned int numeroDeCartaAleatorio = rand() % 6;
        Carta * nuevaCarta = cartasDisponibles->obtener(numeroDeCartaAleatorio);
        this->mazo->push(nuevaCarta);
    }


    this->jugadaAnterior[0][0] = -1;
    this->jugadaAnterior[1][0] = -1;
}

Juego::~Juego() {
    delete this->tablero;

    this->jugadores->iniciarCursor();
    while( this->jugadores->avanzarCursor ) {
        delete this->jugadores->getCursor();
    }
    delete this->jugadores;

    while( ! this->mazo->estaVacia() ) {
        delete this->mazo->pop();
    }
    delete this->mazo;

    delete->this->interfaz;
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


// void Juego::repartirCartas() {
//   // inicia el cursor en nulo
//   this->jugadores->iniciarCursor();
//   // apunto al primer nodo que apunta a jugador
//   this->jugadores->avanzarCursor();
//   // itero la lista de jugadores
//   for( int i = 0; i < this->cantidadJugadores; i++ ) {
//     // saco carta del mazo
//     Carta * nuevaCarta = this->mazo->pop();
//     // entrego carta al jugador i
//     Jugador * jugador = this->jugadores->obtenerCursor();
//     jugador->tomarCarta(nuevaCarta);
//     // avanzo al siguiente nodo que apunta al sig jugador
//     this->jugadores->avanzarCursor();
//   }
// }

void Juego::entregarCarta() {
  if(this->jugadorEnTurno->getCantidadDeCartas() < this->cantidadMaximaCartas) {
    Carta * nuevaCarta = this->mazo->pop();
    this->jugadorEnTurno->tomarCarta(nuevaCarta);
  }
}


void Juego::activarCarta( unsigned int numeroDeCarta ) {

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
            volverJugadaAtras();
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


void Juego::jugar() {

  // while() {
  //   try {
  //     casilleroDestino = pedirCoordenadas
  //     if(sePuedeMover) {
  //       this->jugadorEnTurno->moverFicha(casilleroOrigen, casilleroDestino);
  //     }
  //     break;
  //   } catch() {
  //
  //   }
  // }

}


void Juego::volverJugadaAtras() {

    if ( this->jugadaAnterior[1][0] == -1 ) {
        // NO hubo jugadas, recien inicia el juego
        return;
    }

    int x2 = this->jugadaAnterior[1][0];
    int y2 = this->jugadaAnterior[1][1];
    int z2 = this->jugadaAnterior[1][2];

    Ficha * ficha = this->tablero->getCasillero(x2, y2. z2)->quitarFicha();

    if ( this->jugadaAnterior[0][0] == -1 ) {
        devolverFichaAJugadorAnterior();
        delete ficha;

    } else {
        int x1 = this->jugadaAnterior[0][0];
        int y1 = this->jugadaAnterior[0][1];
        int z1 = this->jugadaAnterior[0][2];

        this->tablero->getCasillero(x1, y1. z1)->setFicha(ficha);
    }
}


void Juego::devolverFichaAJugadorAnterior() {

    int indice = 0;
    this->jugadores->iniciarCursor();
    this->jugadores->avanzarCursor();
    while ( this->jugadores->obtenerCursor() != this->jugadorEnTurno ) {
        this->jugadores->avanzarCursor();
        ++indice;
    }

    Jugador * jugadorAnterior = this->jugadores->obtener(indice);
    jugadorAnterior->incrementarFichas();
}
