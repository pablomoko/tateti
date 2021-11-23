#include "Juego.h"

Juego::Juego() {

    this->interfaz = new Interfaz();    //Se crea objeto interfaz con el que se interactuara

    /* Antes que nada se piden la cantidad de jugadores y fichas al usuario
     * para luego poder generar la lista de jugadores */
    unsigned int cantidadJugadores = pedirCantidadJugadores();
    unsigned int cantidadFichas = pedirCantidadFichas();

    //Se crea la lista de jugadores con sus respectivos nombres y fichas
    this->jugadores = new Lista < Jugador * >;
    for (unsigned int i = 0; i < cantidadJugadores; i++) {
        std::string nombre = pedirNombre(i + 1); // i + 1 es el número de jugador al que corresponde el nombre
        Ficha * ficha = new Ficha('A' + i); //'A' + i para recorrer la tabla ASCII y asignar distintos caracteres
        Jugador * nuevoJugador = new Jugador(nombre, ficha, cantidadFichas);
        this->jugadores->altaFinal(nuevoJugador);
    }
    this->jugadorEnTurno = this->jugadores->obtener(1); //Se establece el jugador 1 como el jugador en turno

    //Se pide al usuario las dimensiones deseadas para cada plano del tablero y se crea uno con las mismas
    unsigned int dimensiones[3] = pedirDimensionesTablero();
    this->tablero = new Tablero(dimensiones[0], dimensiones[1], dimensiones[2]);

    //Se pide al usuario la cantidad maxima de cartas que se puede tener en mano
    this->cantidadMaximaCartas = pedirCantidadCartasPorJugador();

    //Se crea el mazo con una cola de cartas ordenadas (no disponemos del uso del módulo random)
    this->mazo = new Cola < Carta * >;
    for (int i = 0; i < cantidadJugadores * this->cantidadMaximaCartas * 100; i++) {
        // mejorar implementacion (no usar random)
        unsigned int numeroDeCartaAleatorio = rand() % 6;
        Carta * nuevaCarta = cartasDisponibles->obtener(numeroDeCartaAleatorio);
        this->mazo->push(nuevaCarta);
    }

    //Se declaran las coordenadas de la ultima jugada con valores invalidos
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
        return;
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

void Juego::ponerFicha(unsigned int x, unsigned int y, unsigned int z) {
    // validar las coordenadas ???
    Casillero * casilleroDestino = this->tablero->getCasillero(x, y, z);

    // if(casilleroDestino->estaDisponible()) --> estaDisponible chequea que este desbloqueado y vacio ??
    if(casilleroDestino->estaVacio() && casilleroDestino->estaDesbloqueado()) {
        Ficha * fichaJugador = this->jugadorEnTurno->getFicha();
        Ficha * nuevaFicha = new Ficha(fichaJugador);
        casilleroDestino->setFicha(nuevaFicha);
        // si las fichas del jugador fuera una lista directamente le paso la ficha en lugar de crearla
        //  Ficha * fichaJugador = this->jugadorEnTurno->getFicha();
        //  casilleroDestino->setFicha(fichaJugador);
    } else {
      // si el casillero no esta disponible tira error y de afuera tienen que volver a llamar a la funcion con otras coordenadas
      throw "El casillero esta ocupado o bloqueado";
    }
}

void Juego::moverFicha(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int x2, unsigned int y2, unsigned int z2) {
    // validar coordenadas ??
    Casillero * casilleroOrigen = this->tablero->getCasillero(x1, y1, z1);
    Casillero * casilleroDestino = this->tablero->getCasillero(x2, y2, z2);
    Ficha * fichaJugador = this->jugadorEnTurno->getFicha();

    if (casilleroDestino->estaDisponible() && casilleroOrigen->Ocupado()) {
        Ficha * fichaOrigen = casilleroOrigen->getFicha();
        // primero chequea que la ficha sea la del jugador
        // luego la quita y asigna
        if(fichaOrigen == fichaJugador /* fichaOrigen->esIgual(fichaJugador) */) {
            casilleroOrigen->quitarFicha(); // devuelve esa ficha
            casilleroDestino->setFicha(fichaOrigen);
        } else {
          throw "El jugador no puede mover esta ficha";
        }
    } else {
      throw "El casillero no esta disponible";
    }
}

std::string Juego::pedirNombre(int jugadorNumero) {
    std::string nombre[50];

    this->interfaz->pedirNombre(int jugadorNumero);
    std::cin >> nombre;

    return nombre;
}

unsigned int Juego::pedirCantidadJugadores() {
    unsigned int cantidadJugadores = 0;

    this->interfaz->pedirCantidadJugadores();

    try {
        std::cin >> cantidadJugadores;
        if (cantidadJugadores == 0){
            throw "Error 0 jugadores";
        }
    } catch (...) { //En caso de que ingrese un valor inválido se le indica al usuario que lo que ingreso es inválido
        this->interfaz->ingresoInvalido();
    }

    return cantidadJugadores;
}
