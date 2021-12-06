#include "Juego.h"



Juego::Juego() {

    this->interfaz = new Interfaz();
    this->ganador = NULL;
    this->jugadorAnterior = NULL;


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


    unsigned int * dimensiones = new unsigned int [3];
    pedirDimensionesTablero(cantidadJugadores, cantidadFichas, dimensiones);
    this->tablero = new Tablero(dimensiones[0], dimensiones[1], dimensiones[2]);
    delete []dimensiones;


    this->cantidadMaximaCartas = pedirCantidadCartasPorJugador();

    this->mazo = new Cola < Carta * >;
    for (unsigned int i = 0; i < cantidadJugadores*cantidadMaximaCartas*2; i++) {
        funcion_t funcionalidad = getFuncionalidad(i % 6);
        Carta * nuevaCarta = new Carta(funcionalidad);
        this->mazo->push(nuevaCarta);
    }

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

	this->jugadorAnterior = this->jugadorEnTurno;

	if ( this->jugadorEnTurno->getNumeroDeTurnos() == 2 ) {
		this->jugadorEnTurno->unTurno();
		return;
	}

	this->jugadores->iniciarCursor();

  while ( this->jugadores->avanzarCursor() ) {

    if( this->jugadorEnTurno == jugadores->obtenerCursor() ) {

      if ( !(jugadores->avanzarCursor() ) ) {
        this->jugadores->iniciarCursor();
        this->jugadores->avanzarCursor();
      }

      if ( jugadores->obtenerCursor()->getNumeroDeTurnos() == 0 ) {
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
}


void Juego::entregarCarta() {
  if(this->jugadorEnTurno->getCantidadDeCartas() < this->cantidadMaximaCartas) {
    Carta * nuevaCarta = this->mazo->pop();
    this->jugadorEnTurno->tomarCarta(nuevaCarta);
  }
}


// ===============================================
// ============= FUNCIONES DE CARTAS =============


void Juego::activarCarta( funcion_t funcionalidad ) {


	Carta * carta = this->jugadorEnTurno->usarCarta( funcionalidad );

	this->mazo->push(carta);


    switch (funcionalidad) {

        case SALTEAR:
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
    bool encontrado = false;

    while( this->jugadores->avanzarCursor() && !encontrado ) {

        if ( this->jugadorEnTurno == this->jugadores->obtenerCursor() ) {

            if ( this->jugadores->avanzarCursor() ) {
                this->jugadores->obtenerCursor()->saltear();
                encontrado = true;
            } else {
                this->jugadores->iniciarCursor();
                this->jugadores->avanzarCursor();
                this->jugadores->obtenerCursor()->saltear();
                encontrado = true;
            }
        }
    }
}


void Juego::volverJugadaAtras() {

    if ( this->jugadaAnterior[1][0] == -1 ) {
        return;
    }

    int x2 = this->jugadaAnterior[1][0];
    int y2 = this->jugadaAnterior[1][1];
    int z2 = this->jugadaAnterior[1][2];

    Ficha * ficha = this->tablero->getCasillero(x2, y2, z2)->quitarFicha();

    if ( this->jugadaAnterior[0][0] == -1 ) {
        devolverFichaAJugadorAnterior();

    } else {
        int x1 = this->jugadaAnterior[0][0];
        int y1 = this->jugadaAnterior[0][1];
        int z1 = this->jugadaAnterior[0][2];

        try {
        	this->tablero->getCasillero(x1, y1, z1)->setFicha(ficha);
        }
        catch (...) {

        	devolverFichaAJugadorAnterior();
        }
    }
    delete ficha;
}


void Juego::devolverFichaAJugadorAnterior() {

	this->jugadorAnterior->incrementarCantidadFichas();
}


Jugador * Juego::obtenerJugadorSiguiente(){

    this->jugadores->iniciarCursor();
    
    while( this->jugadores->avanzarCursor() ){

        if(this->jugadorEnTurno == this->jugadores->obtenerCursor() ){

        	if ( this->jugadores->avanzarCursor() ) {
                return this->jugadores->obtenerCursor();
            }
            else {
            	break;
            }
        }
    }

    this->jugadores->iniciarCursor();
    this->jugadores->avanzarCursor();
    return this->jugadores->obtenerCursor();
}


// ===============================================
// ======== FUNCIONES DE ENTRADA DE DATOS ========


unsigned int Juego::pedirCantidadJugadores() {

	int cantidadJugadores = 0;
	bool cantidadValida = false;

    while ( !cantidadValida ) {

    	this->interfaz->pedirCantidadJugadores();
        try {
            std::cin >> cantidadJugadores;
            if (cantidadJugadores < 2){
                throw "Error Menos de 2 jugadores";
            }
            cantidadValida = true;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    return (unsigned int) cantidadJugadores;
}


unsigned int Juego::pedirCantidadFichas() {

    int cantidadFichas = 0;
    bool cantidadValida = false;

    while (!cantidadValida) {
        this->interfaz->pedirCantidadFichas();
        try {
            std::cin >> cantidadFichas;
            if (cantidadFichas < 3){
                throw "Error menos de 3 fichas";
            }
            cantidadValida = true;
        } catch (...) { //En caso de que ingrese un valor inválido se le indica al usuario que lo que ingreso es inválido
            this->interfaz->ingresoInvalido();
        }
    }

    return (unsigned int) cantidadFichas;
}


std::string Juego::pedirNombre(int jugadorNumero) {
    std::string nombre;
    bool nombreValido = false;

    while ( !nombreValido ) {
        this->interfaz->pedirNombre(jugadorNumero);
        try {
            std::cin >> nombre;
            if (nombre.length() > 10) {
                throw("Nombre demasiado largo.");
            }
            nombreValido = true;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }
    return nombre;
}


void Juego::pedirDimensionesTablero(int cantidadJugadores, int cantidadFichas, unsigned int * dimensiones) {

    int ancho, alto, profundo;
    bool dimensionesValidas = false;

    while ( !dimensionesValidas ) {
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
            dimensionesValidas = true;

        } catch (...) {
        	this->interfaz->tableroChico();
        }
    }

    dimensiones[0] = ancho; dimensiones[1] = alto; dimensiones[2] = profundo;
}


unsigned int Juego::pedirCantidadCartasPorJugador() {

    int cantidadCartas;
    bool cantidad_valida = false;

    while ( !cantidad_valida ) {

        this->interfaz->pedirCantidadCartas();
        try {
            std::cin>>cantidadCartas;
            if ( cantidadCartas < 1 ) {
                throw("Cada jugador debe tener al menos una carta.");
            }
            cantidad_valida = true;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    return (unsigned int)cantidadCartas;
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

    throw("Numero de carta no valido");

}


// ===============================================
// ========= FUNCIONES DE COORDENADAS ============


Casillero * Juego::pedirCoordenadasB( int * coordenadas = NULL ) {

    Casillero * casillero;
    unsigned int x, y, z;
    bool ingreso_valido = false;

    while (!ingreso_valido) {
        try {
            std::cout<<"Ancho:  \t";
            std::cin>>x;
            --x;

            std::cout<<"Alto:   \t";
            std::cin>>y;
            --y;

            std::cout<<"Profundo:  \t";
            std::cin>>z;
            --z;

            casillero = this->tablero->getCasillero(x, y, z);

            ingreso_valido = true;
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
    bool ingreso_valido = false;

    while (!ingreso_valido) {
        try {
            std::cout<<"Ancho:   \t";
            std::cin>>x;
            --x;

            std::cout<<"Alto:    \t";
            std::cin>>y;
            --y;

            std::cout<<"Profundo:  \t";
            std::cin>>z;
            --z;

            casillero = this->tablero->getCasillero(x, y, z);

            ingreso_valido = true;
        } catch (...) {
            this->interfaz->ingresoInvalido();
        }
    }

    return casillero;
}


// ===============================================
// =========== FUNCIONES PRINCIPALES =============


void Juego::ponerFicha( int ** jugadaActual ) {

	Casillero * casilleroDestino;
	bool coordenadas_validas = false;

    while (!coordenadas_validas) {

        this->interfaz->pedirCoordPonerFicha();
        casilleroDestino = this->pedirCoordenadasB( jugadaActual[1] ); // casillero existente
        jugadaActual[0][0] = -1 ;jugadaActual[0][1] = -1; jugadaActual[0][2] = -1;
        Ficha * nuevaFicha;
        try {
        	nuevaFicha = this->jugadorEnTurno->getFicha();
        	casilleroDestino->setFicha( nuevaFicha );
            coordenadas_validas = true;
        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
        }
    }

    this->jugadorEnTurno->disminuirCantidadFichas();
}



void Juego::moverFicha( int ** jugadaActual ) {

    Ficha * ficha;
    Casillero * casilleroOrigen;
    bool coordenadas_validas = false;

    while (!coordenadas_validas) {

        this->interfaz->pedirCoordOrigenMoverFicha();
        casilleroOrigen = this->pedirCoordenadasB( jugadaActual[0] );
        try {

            ficha = casilleroOrigen->getFicha();

            if ( ! ficha->esIgual( this->jugadorEnTurno->getFicha()) ||
            		ficha->estaBloqueada()  ) {
                throw("La ficha que intenta mover no le pertenece al jugador actual o esta bloqueada.");
            }


        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
            continue;
        }

        this->interfaz->pedirCoordDestinoMoverFicha();
        Casillero * casilleroDestino = this->pedirCoordenadasB( jugadaActual[1] );

        try {
            if ( ! casilleroOrigen->esAdyacenteLineal(casilleroDestino) ) {
                throw("El casillero de destino no es un adyacente recto.");
            }
            casilleroDestino->setFicha( ficha );

        } catch (...) {
            this->interfaz->informarCasilleroNoDisponible();
            continue;
        }

        delete casilleroOrigen->quitarFicha();

        coordenadas_validas = true;
    }
}



void Juego::usarCarta() {

    char respuesta;
    int numeroCarta;
    bool cartaValida = false;

    while (!cartaValida) {

        this->interfaz->preguntarUsarCarta();
        std::cin>>respuesta;
        if ( respuesta == 'N' ) {
            return;
        } else if ( respuesta != 'S' ) {
            continue;
        }

        this->interfaz->preguntarNroCarta();
        std::cin>>numeroCarta;

        try {
        	this->activarCarta( this->getFuncionalidad(numeroCarta-1) );
        }
        catch (...) {
        	this->interfaz->jugadorNoTieneCartaElegida();
        	continue;
        }

        cartaValida = true;
    }
}


// ===============================================
// ===============================================


bool Juego::hayTateti(Casillero * casilleroOrigen){

	int longitudesAdyacentes[3][3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
               
                longitudesAdyacentes[i][j][k] = casilleroOrigen->getLongitudFichasIguales(i, j, k);
            }
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if ((longitudesAdyacentes[i][j][k] + 1 == 3)|| //Caso tateti siguiendo una direccion
                    (longitudesAdyacentes[i][j][k] + 1 + longitudesAdyacentes[2-i][2-j][2-k] == 3)){ //Caso tateti en un adyacente y su opuesto
                    this->ganador = this->jugadorEnTurno;
                	return true;
                }
            }
        }
    }

    return false;
}


// ===============================================
// ===============================================

void Juego::jugar() {

	this->interfaz->mostrarPantallaInicial();

	this->interfaz->mostrarControles(this->tablero);

    int ** jugadaActual = new int* [2];
    jugadaActual[0] = new int [3];
    jugadaActual[1] = new int [3];

    while ( !(this->ganador) ) {

    	this->interfaz->mostrarTablero(this->tablero);

        this->entregarCarta();

        if ( this->jugadorEnTurno->getCantidadFichas() > 0 ) {
            this->interfaz->tocaPonerFicha( this->jugadorEnTurno->getNombre(), this->jugadorEnTurno->getFicha()->getSimbolo(),
            								this->jugadorEnTurno->getCantidadFichas() );
            this->ponerFicha( jugadaActual );
        }

        else {
            this->interfaz->tocaMoverFicha( this->jugadorEnTurno->getNombre(), this->jugadorEnTurno->getFicha()->getSimbolo() );
            this->moverFicha( jugadaActual );
        }

        this->interfaz->mostrarTablero(this->tablero);

        Casillero * casillero = this->tablero->getCasillero(jugadaActual[1][0], jugadaActual[1][1], jugadaActual[1][2]);
        if ( this->hayTateti(casillero) ) {
            break;
        }

        if ( this->jugadorEnTurno->getCantidadDeCartas() > 0 ) {
            this->interfaz->mostrarCartasJugador(jugadorEnTurno->getNombre(), jugadorEnTurno->getCartas());
            this->usarCarta();
        } else {
            this->interfaz->jugadorSinCartas();
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                this->jugadaAnterior[i][j] = jugadaActual[i][j];
            }
        }

        this->cambiarTurno();

    }

    this->interfaz->mostrarTablero(this->tablero);
    this->interfaz->mostrarGanador(this->jugadorEnTurno->getNombre());

    delete [] jugadaActual[0];
    delete [] jugadaActual[1];
    delete [] jugadaActual;

}


