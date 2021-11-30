#include "Juego.h"



Juego::Juego() {

    this->interfaz = new Interfaz();    //Se crea objeto interfaz con el que se interactuara
    this->ganador = NULL;   // Como recien empieza el juego, se crea en nulo


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
    unsigned int * dimensiones = new unsigned int [3];
    pedirDimensionesTablero(cantidadJugadores, cantidadFichas, dimensiones);
    this->tablero = new Tablero(dimensiones[0], dimensiones[1], dimensiones[2]);
    delete []dimensiones;

    //Se pide al usuario la cantidad maxima de cartas que se puede tener en mano
    this->cantidadMaximaCartas = pedirCantidadCartasPorJugador();

    //Se crea el mazo con una cola de cartas ordenadas (no disponemos del uso del módulo random)
    this->mazo = new Cola < Carta * >;
    for (unsigned int i = 0; i < cantidadJugadores*cantidadMaximaCartas*2; i++) {
        funcion_t funcionalidad = getFuncionalidad(i % 6);
        Carta * nuevaCarta = new Carta(funcionalidad);
        this->mazo->push(nuevaCarta);
    }

    //Se declaran las coordenadas de la ultima jugada con valores invalidos
    this->jugadaAnterior[0][0] = -1;this->jugadaAnterior[0][1] = -1;this->jugadaAnterior[0][2] = -1;
    this->jugadaAnterior[1][0] = -1;this->jugadaAnterior[1][1] = -1;this->jugadaAnterior[1][2] = -1;
}


Juego::~Juego() {
    delete this->tablero;

    this->jugadores->iniciarCursor();
    while( this->jugadores->avanzarCursor() ) {
        delete this->jugadores->obtenerCursor();
    }
    delete this->jugadores;

    while( ! this->mazo->estaVacia() ) {
        delete this->mazo->pop();
    }
    delete this->mazo;

    delete this->interfaz;
}


void Juego::cambiarTurno() {

  // inicia el cursor en nulo
  this->jugadores->iniciarCursor();
  // itero la lista en busca del jugador en turno
  while ( this->jugadores->avanzarCursor() ) {
    // apunto al primer jugador

    if( this->jugadorEnTurno == jugadores->obtenerCursor() ) {
      // si es el jugador en turno, avanzo uno mas (si llega al final empiezo de nuevo)

      if ( !(jugadores->avanzarCursor() ) ) {
        this->jugadores->iniciarCursor();
        this->jugadores->avanzarCursor();
      }

      if ( jugadores->obtenerCursor()->getNumeroDeTurnos() == 0 ) {
        //si el sig jugador esta bloqueado, avanzo uno mas, y lo desbloqueo para la proxima
        jugadores->obtenerCursor()->unTurno();
        jugadores->avanzarCursor();
      }

      try {
          this->jugadorEnTurno = jugadores->obtenerCursor();
      } catch (...) {
        this->jugadores->iniciarCursor();
        this->jugadores->avanzarCursor();
        this->jugadorEnTurno = jugadores->obtenerCursor();
      }


      return;
    }
  }
  // con esta solucion se itera la lista cada vez que se cambia el turno.
  // no es gran problema porque la cantidad de jugadores va a ser 2,3,4,5... a lo sumo 10
}


void Juego::entregarCarta() {
  if(this->jugadorEnTurno->getCantidadDeCartas() < this->cantidadMaximaCartas) {
    Carta * nuevaCarta = this->mazo->pop();
    this->jugadorEnTurno->tomarCarta(nuevaCarta);
  }
}


void Juego::activarCarta( funcion_t funcionalidad ) {

    try {
        Carta * carta = this->jugadorEnTurno->usarCarta( funcionalidad );
        // Si el jugador no tiene esa carta, tira error

        this->mazo->push(carta); // agrego la carta usada al final del mazo
    }
    catch (...) {
        return;
    }


    switch (funcionalidad) {

        case SALTEAR:
            // Hacer perder un turno al siguiente jugador
            this->saltearSiguienteJugador();
            break;

        case BLOCK_FICHA:
            this->interfaz->pedirPosicionFichaABloquear();
            try {
                Casillero * casillero = this->pedirCoordenadas();
                if ( casillero->estaVacio() ) {
                    throw("No hay ficha en el casillero para bloquear");
                }
                casillero->getFicha()->bloquear();
            }
            catch (...) {
                this->interfaz->informarNoHayFicha();
            }
            break;

        case BLOCK_CASILLERO:
            this->interfaz->pedirPosicionCasilleroABloquear();
            try {
                Casillero * casillero = this->pedirCoordenadas();
                casillero->bloquear();
            }
            catch (...) {

            }
            break;

        case REGRESAR:
            volverJugadaAtras();
            break;

        case REPETIR:
            this->jugadorEnTurno->dobleTurno();
            break;

        case ROBAR_CARTA:
            try{
                  Jugador *jugadorElegido = this->obtenerJugadorSiguiente();
                  Carta *carta = jugadorElegido->getUltimaCarta();
                  this->jugadorEnTurno->tomarCarta(carta);
            }
            catch(...){
            }

            break;
    }
}


void Juego::saltearSiguienteJugador() {

    this->jugadores->iniciarCursor();

    while( this->jugadores->avanzarCursor() ) {

        if ( this->jugadorEnTurno == this->jugadores->obtenerCursor() ) {

            if ( this->jugadores->avanzarCursor() ) {
                this->jugadores->obtenerCursor()->saltear();
            } else {
                this->jugadores->iniciarCursor();
                this->jugadores->avanzarCursor();
                this->jugadores->obtenerCursor()->saltear();
            }
        }
    }
}


void Juego::volverJugadaAtras() {

    if ( this->jugadaAnterior[1][0] == -1 ) {
        // NO hubo jugadas, recien inicia el juego
        return;
    }

    int x2 = this->jugadaAnterior[1][0];
    int y2 = this->jugadaAnterior[1][1];
    int z2 = this->jugadaAnterior[1][2];

    Ficha * ficha = this->tablero->getCasillero(x2, y2, z2)->quitarFicha();

    if ( this->jugadaAnterior[0][0] == -1 ) {
        devolverFichaAJugadorAnterior();
        delete ficha;

    } else {
        int x1 = this->jugadaAnterior[0][0];
        int y1 = this->jugadaAnterior[0][1];
        int z1 = this->jugadaAnterior[0][2];

        this->tablero->getCasillero(x1, y1, z1)->setFicha(ficha);
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
    jugadorAnterior->incrementarCantidadFichas();
}


Jugador * Juego::obtenerJugadorSiguiente(){

    this->jugadores->iniciarCursor();
    
    while( this->jugadores->avanzarCursor() ){

        if(this->jugadorEnTurno == this->jugadores->obtenerCursor() ){
            
            if ( this->jugadores->avanzarCursor() ) {
                return this->jugadores->obtenerCursor();
            }
        }
    }

    this->jugadores->iniciarCursor();
    this->jugadores->avanzarCursor();
    return this->jugadores->obtenerCursor();
}



// ===============================================
// ===============================================


unsigned int Juego::pedirCantidadJugadores() {
    unsigned int cantidadJugadores = 0;

    this->interfaz->pedirCantidadJugadores();

    while (true) {
        try {
            std::cin >> cantidadJugadores;
            if (cantidadJugadores < 2){
                throw "Error Menos de 2 jugadores";
            }
            break;
        } catch (...) { //En caso de que ingrese un valor inválido se le indica al usuario que lo que ingreso es inválido
            this->interfaz->ingresoInvalido();
        }
    }

    return cantidadJugadores;
}


unsigned int Juego::pedirCantidadFichas() {

    unsigned int cantidadFichas = 0;

    while (true) {
        this->interfaz->pedirCantidadFichas();
        try {
            std::cin >> cantidadFichas;
            if (cantidadFichas < 3){
                throw "Error menos de 3 fichas";
            }
            break;
        } catch (...) { //En caso de que ingrese un valor inválido se le indica al usuario que lo que ingreso es inválido
            this->interfaz->ingresoInvalido();
        }
    }

    return cantidadFichas;
}


std::string Juego::pedirNombre(int jugadorNumero) {
    std::string nombre;

    while ( true ) {
        this->interfaz->pedirNombre(jugadorNumero);
        try {
            std::cin >> nombre;
            if (nombre.length() > 10) {
                throw("Nombre demasiado largo.");
            }
            break;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }
    return nombre;
}


void Juego::pedirDimensionesTablero(unsigned int cantidadJugadores, unsigned int cantidadFichas, unsigned int * dimensiones) {

    unsigned int ancho, alto, profundo;

    while ( true ) {
        this->interfaz->pedirDimensiones();
        try {
            std::cout<<"Ancho:  \t";
            std::cin>>ancho;

            std::cout<<"Alto:   \t";
            std::cin>>alto;

            std::cout<<"Profundo:  \t";
            std::cin>>profundo;

            if ( ancho<1 || alto<1 || profundo<1 ||
                    ancho*alto*profundo<cantidadJugadores*cantidadFichas+cantidadJugadores ) {
                throw("Coordenadas invalidas o talbero demasiado chico.");
            }
            break;

        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    //unsigned int * coordenadas = new unsigned int [3];
    dimensiones[0] = ancho; dimensiones[1] = alto; dimensiones[2] = profundo;
    //return dimensiones;
}


unsigned int Juego::pedirCantidadCartasPorJugador() {

    unsigned int cantidadCartas;

    while ( true ) {

        this->interfaz->pedirCantidadCartas();
        try {
            std::cin>>cantidadCartas;
            if ( cantidadCartas < 1 ) {
                throw("Cada jugador debe tener al menos una carta.");
            }
            break;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    return cantidadCartas;
}


funcion_t Juego::getFuncionalidad(unsigned int indice) {

    switch (indice) {
    case SALTEAR:
        return SALTEAR;

    case BLOCK_FICHA:
        return BLOCK_FICHA;

    case BLOCK_CASILLERO:
        return BLOCK_CASILLERO;

    case REGRESAR:
        return REGRESAR;

    case REPETIR:
        return REPETIR;

    case ROBAR_CARTA:
        return ROBAR_CARTA;
    };

    return SALTEAR;
}


Casillero * Juego::pedirCoordenadasB( int * coordenadas = NULL ) {

    Casillero * casillero;
    unsigned int x, y, z;

    while (true) {
        try {
            std::cout<<"Ancho:  \t";
            std::cin>>x;

            std::cout<<"Alto:   \t";
            std::cin>>y;

            std::cout<<"Profundo:  \t";
            std::cin>>z;

            casillero = this->tablero->getCasillero(x, y, z);

            break;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    if ( coordenadas ) {
        coordenadas[0] = x;
        coordenadas[1] = y;
        coordenadas[2] = z;
    }

    return casillero;
}


Casillero * Juego::pedirCoordenadas() {

    Casillero * casillero;
    unsigned int x, y, z;

    while (true) {
        try {
            std::cout<<"Ancho: \t";
            std::cin>>x;

            std::cout<<"Alto:  \t";
            std::cin>>y;

            std::cout<<"Profundo:  \t";
            std::cin>>z;

            casillero = this->tablero->getCasillero(x, y, z);

            break;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    return casillero;
}


// ===============================================
// ===============================================

void Juego::ponerFicha( int ** jugadaActual ) {

    while (true) {

        this->interfaz->pedirCoordPonerFicha();
        Casillero * casilleroDestino = this->pedirCoordenadasB( jugadaActual[1] ); // casillero existente
        jugadaActual[0][0] = -1;jugadaActual[0][1] = -1;jugadaActual[0][2] = -1;

        try {

            casilleroDestino->setFicha( this->jugadorEnTurno->getFicha() );
                //Que tire error

            break;
        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
        }
    }

    this->jugadorEnTurno->disminuirCantidadFichas();
    //std::cout<<"\nEl jugador: "<<this->jugadorEnTurno->getNombre()<<" tiene "<<this->jugadorEnTurno->getCantidadFichas()<<" fichas.\n";
}



void Juego::moverFicha( int ** jugadaActual ) {

    while (true) {

        this->interfaz->pedirCoordOrigenMoverFicha();
        Casillero * casilleroOrigen = this->pedirCoordenadasB( jugadaActual[0] ); // casillero existente
        Ficha * ficha;
        try {

            ficha = casilleroOrigen->getFicha();
                //Que tire error si: casillero vacio, bloqueado o ficha bloqueada

            if ( ! ficha->esIgual( this->jugadorEnTurno->getFicha() ) ) {
                throw("La ficha que intenta mover no le pertenece al jugador actual.");
            }

        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
            continue;
        }

        this->interfaz->pedirCoordDestinoMoverFicha();
        Casillero * casilleroDestino = this->pedirCoordenadasB( jugadaActual[1] ); // casillero existente

        try {
            if ( ! casilleroOrigen->esAdyacente(casilleroDestino) ) {
            //if ( ! casilleroOrigen->adyacenteRecto(casilleroDestino) ) {
                // Se puede mover a adyacente que no sea oblicuo
                throw("El casillero de destino no es un adyacente recto.");
            }
            casilleroDestino->setFicha( ficha );

        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
            continue;
        }

        casilleroOrigen->quitarFicha();

        break;
    }
}



void Juego::usarCarta() {

    while (true) {

        this->interfaz->preguntarUsarCarta();
        char respuesta;
        std::cin>>respuesta;
        if ( respuesta == 'N' ) {
            return;
        } else if ( respuesta != 'S' ) {
            continue;
        }

        this->interfaz->preguntarNroCarta();
        int numeroCarta;
        std::cin>>numeroCarta;
        this->activarCarta( this->getFuncionalidad(numeroCarta-1) );

        return;
    }
}


// ===============================================
// ===============================================

bool Juego::hayTateti(Casillero * casilleroOrigen){
    int longitudesAdyacentes[3][3][3];  //Longitud de vector de adyacentes en cada direccion

    //En esta iteracion se guardan la cantidad de casilleros con fichas iguales en cada direccion
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                /*
                 * Se guarda la longitud de un vector con origen en casilleroOrigen
                 * en la posicion del array correspondiente a cada iteracion
                 */
                longitudesAdyacentes[i][j][k] = casilleroOrigen->getLongitudFichasIguales(i, j, k);
            }
        }
    }

    /*
     * Una vez tenemos la cantidad de fichas iguales en cada direccion respecto de casilleroOrigen,
     * se checkea si en alguna direccion hay 3 y en caso de que si se devuelve true
     */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if ((longitudesAdyacentes[i][j][k] + 1 == 3)|| //Caso tateti siguiendo una direccion
                    (longitudesAdyacentes[i][j][k] + 1 + longitudesAdyacentes[2-i][2-j][2-k] == 3)){ //Caso tateti en un adyacente y su opuesto
                    return true
                }
            }
        }
    }

    return false
}

// ===============================================
// ===============================================

void Juego::jugar() {


    //int jugadaActual[2][3];
    int ** jugadaActual = new int* [2];
    jugadaActual[0] = new int [3];
    jugadaActual[1] = new int [3];

    while (true) { // Mientras que no haya ganador

        /*
        std::cout<<"\n\n   =========   INICIO DEL TURNO   =========  ";
        std::cout<<"\nJugada anterior:";
        std::cout<<"\nOrigen: ("<<this->jugadaAnterior[0][0]<<" "<<this->jugadaAnterior[0][1]<<" "<<this->jugadaAnterior[0][2]<<")";
        std::cout<<"\nDestino: ("<<this->jugadaAnterior[1][0]<<" "<<this->jugadaAnterior[1][1]<<" "<<this->jugadaAnterior[1][2]<<")";
        std::cout<<"\n\n";
        */

        this->interfaz->mostrarTablero(this->tablero);

        this->entregarCarta();

        //std::cout<<"\nEl jugador: "<<this->jugadorEnTurno->getNombre()<<" tiene "<<this->jugadorEnTurno->getCantidadFichas()<<" fichas.\n";
        if ( this->jugadorEnTurno->getCantidadFichas() > 0 ) {
            this->interfaz->tocaPonerFicha( this->jugadorEnTurno->getNombre() );
            this->ponerFicha( jugadaActual );
        }

        else {
            this->interfaz->tocaMoverFicha( this->jugadorEnTurno->getNombre() );
            this->moverFicha( jugadaActual );
        }

        /*
        std::cout<<"\n\nJugada actual:";
        std::cout<<"\nOrigen: ("<<jugadaActual[0][0]<<" "<<jugadaActual[0][1]<<" "<<jugadaActual[0][2]<<")";
        std::cout<<"\nDestino: ("<<jugadaActual[1][0]<<" "<<jugadaActual[1][1]<<" "<<jugadaActual[1][2]<<")";
        std::cout<<"\n\n";
        */

        Casillero * casillero = this->tablero->getCasillero(jugadaActual[1][0], jugadaActual[1][1], jugadaActual[1][2]);
        if ( this->tablero->hayTateti(casillero) ) {
            break;
        }

        if ( this->jugadorEnTurno->getCantidadDeCartas() > 0 ) {
            this->interfaz->mostrarCartasJugador(jugadorEnTurno->getCartas());
            this->usarCarta();
        } else {
            this->interfaz->jugadorSinCartas();
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                this->jugadaAnterior[i][j] = jugadaActual[i][j];
            }
        }

        if ( jugadorEnTurno->getNumeroDeTurnos() == 1 ) {
            // si le jugador tiene doble turno, no entra aca
            this->cambiarTurno();
        } else {
            jugadorEnTurno->unTurno();
        }
    }

    this->interfaz->mostrarTablero(this->tablero);
    this->interfaz->mostrarGanador(this->jugadorEnTurno->getNombre());

    delete [] jugadaActual[0];
    delete [] jugadaActual[1];
    delete [] jugadaActual;

}