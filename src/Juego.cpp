#include "Juego.h"



Juego::Juego() {

    this->interfaz = new Interfaz();
    this->ganador = NULL;
    this->jugadorAnterior = NULL;

    // LA CANTIDAD DE COLORES DETERMINA LA CANTIDAD DE JUGADORES
    Lista < RGBApixel > * colores = new Lista< RGBApixel >;
    Lista < std::string > * strColores = new Lista< std::string >;
    this->crearColores( colores, strColores );

    unsigned int cantidadJugadores = pedirCantidadJugadores();
    unsigned int cantidadFichas = pedirCantidadFichas();


    this->jugadores = new Lista < Jugador * >;
    for (unsigned int i = 0; i < cantidadJugadores; i++) {
        std::string nombre = pedirNombre(i + 1);
        RGBApixel color = colores->obtener(i+1);
        std::string strColor = strColores->obtener(i+1);
        Ficha * ficha = new Ficha('A' + i, color);
        Jugador * nuevoJugador = new Jugador(nombre, ficha, cantidadFichas, strColor);
        this->jugadores->altaFinal(nuevoJugador);
    }
    this->jugadorEnTurno = this->jugadores->obtener(1);

    delete colores;
    delete strColores;


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

    if ( this->jugadaAnterior[1][0] == -1 ) { //Si es el primer movimiento del juego
        return;
    }

    int x2 = this->jugadaAnterior[1][0];
    int y2 = this->jugadaAnterior[1][1];
    int z2 = this->jugadaAnterior[1][2];

    Ficha * ficha = this->tablero->getCasillero(x2, y2, z2)->quitarFicha();
    this->borrarFichaBitmap(x2, y2, z2);

    if ( this->jugadaAnterior[0][0] == -1 ) {
        devolverFichaAJugadorAnterior();

    } else {
        int x1 = this->jugadaAnterior[0][0];
        int y1 = this->jugadaAnterior[0][1];
        int z1 = this->jugadaAnterior[0][2];

        try {
        	this->tablero->getCasillero(x1, y1, z1)->setFicha(ficha);
            this->escribirFichaBitmap(x1, y1, z1);
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

void Juego::crearColores( Lista < RGBApixel > * colores, Lista < std::string > * strColores ) {

    // LA CANTIDAD DE COLORES DETERMINA LA CANTIDAD DE JUGADORES

    RGBApixel red;
	red.Red = 255; red.Green = 0; red.Blue = 0; red.Alpha = 0;
	RGBApixel blue;
	blue.Red = 0; blue.Green = 0; blue.Blue = 255; blue.Alpha = 0;
	RGBApixel yellow;
	yellow.Red = 255; yellow.Green = 255; yellow.Blue = 0; yellow.Alpha = 0;
	RGBApixel green;
	green.Red = 70; green.Green = 200; green.Blue = 60; green.Alpha = 0;
	RGBApixel orange;
	orange.Red = 255; orange.Green = 120; orange.Blue = 0; orange.Alpha = 0;
	RGBApixel violet;
	violet.Red = 110; violet.Green = 80; violet.Blue = 150; violet.Alpha = 0;

    colores->altaFinal(red);
    std::string color = "rojo";
    strColores->altaFinal(color);
    colores->altaFinal(blue);
    color = "azul";
    strColores->altaFinal(color);
    colores->altaFinal(yellow);
    color = "amarillo";
    strColores->altaFinal(color);
    colores->altaFinal(green);
    color = "verde";
    strColores->altaFinal(color);
    colores->altaFinal(orange);
    color = "naranja";
    strColores->altaFinal(color);
    colores->altaFinal(violet);
    color = "violeta";
    strColores->altaFinal(color);
}


void Juego::crearBitmap() {
    
    int ancho = this->tablero->getDimensiones()[0];
    int alto = this->tablero->getDimensiones()[1];
    int profundo = this->tablero->getDimensiones()[2];

    int dimensionCasillero = 50;
    
    int width = dimensionCasillero * ancho * profundo;
    int height = dimensionCasillero * alto;

	BMP image;
	image.SetSize(width,height);
	// Set its color depth to 8-bits	
	image.SetBitDepth(8);

	RGBApixel grey;
	grey.Red = 150; grey.Green = 150; grey.Blue = 150; grey.Alpha = 0;
	RGBApixel black;
	black.Red = 0; black.Green = 0; black.Blue = 0; black.Alpha = 0;
    RGBApixel white;
    white.Red = 255; white.Green = 255; white.Blue = 255; white.Alpha = 0;


	// Pintar toda la imagen de gris
	for ( int y=0; y<height; ++y ) {
		for ( int x=0; x<width ; ++x ) {
			image.SetPixel(x, y, grey);
		}
	}


	// Pintar las lineas separadoras
	for ( int y=0; y<height; ++y ) {

        image.SetPixel(0, y, black);
        image.SetPixel(1, y, black);
        image.SetPixel(width-2, y, black);
        image.SetPixel(width-1, y, black);

		for ( int x=0; x<width ; ++x ) {

            image.SetPixel(x, 0, black);
            image.SetPixel(x, 1, black);
            image.SetPixel(x, height-2, black);
            image.SetPixel(x, height-1, black);

			if ( y%dimensionCasillero==0 || x%dimensionCasillero==0 ) {
                image.SetPixel(x, y, black);
            }
            if ( (x!=0) && (x%(dimensionCasillero*ancho) == 0) ) {
                image.SetPixel(x-1, y, black);
                image.SetPixel(x+1, y, black);
                image.SetPixel(x+2, y, black);
            }
		}
	}

    image.WriteToFile("image.bmp");
}


void Juego::borrarFichaBitmap( int i, int j, int k ) {

    BMP image;
    image.ReadFromFile("image.bmp");

    int ancho = this->tablero->getDimensiones()[0];

    int dimensionCasillero = 50;

    RGBApixel grey;
    grey.Red = 150; grey.Green = 150; grey.Blue = 150; grey.Alpha = 0;

    int min_y = dimensionCasillero*j+1;
    int max_y = dimensionCasillero*(j+1);

    if ( j==0 ) {
        min_y += 1;
    } else if ( j== (this->tablero->getDimensiones()[1]-1) ) {
        max_y -= 2;
    }
    
    for ( int y=min_y; y<max_y; ++y ) {
        
        int min_x = dimensionCasillero*i+1+(dimensionCasillero*ancho*k);
        int max_x = dimensionCasillero*(i+1)+(dimensionCasillero*ancho*k);

        if ( i==0 ) {
            min_x += 1;
            if ( k!=0 ) {
                min_x += 1;
            }
        } else if ( i == (this->tablero->getDimensiones()[0]-1) ) {
            max_x -= 1;

            if (k == (this->tablero->getDimensiones()[2]-1) ) {
                max_x -= 1;
            }
        }
        
        for ( int x=min_x; x<max_x; ++x) {
            image.SetPixel(x, y, grey);
        }
    }

    image.WriteToFile("image.bmp");
}


void Juego::escribirFichaBitmap( int i, int j, int k ) {

    BMP image;
    image.ReadFromFile("image.bmp");

    int ancho = this->tablero->getDimensiones()[0];

    int dimensionCasillero = 50;


    // pinto el casillero a donde se puso una ficha

    Casillero * casillero = this->tablero->getCasillero(i, j, k);
    RGBApixel color = casillero->getFicha()->getColor();

    int min_y = dimensionCasillero*j+1;
    int max_y = dimensionCasillero*(j+1);

    if ( j==0 ) {
        min_y += 1;
    } else if ( j== (this->tablero->getDimensiones()[1]-1) ) {
        max_y -= 2;
    }
    
    for ( int y=min_y; y<max_y; ++y ) {
        
        int min_x = dimensionCasillero*i+1+(dimensionCasillero*ancho*k);
        int max_x = dimensionCasillero*(i+1)+(dimensionCasillero*ancho*k);

        if ( i==0 ) {
            min_x += 1;
            if ( k!=0 ) {
                min_x += 1;
            }
        } else if ( i == (this->tablero->getDimensiones()[0]-1) ) {
            max_x -= 1;

            if (k == (this->tablero->getDimensiones()[2]-1) ) {
                max_x -= 1;
            }
        }
        
        for ( int x=min_x; x<max_x; ++x) {
            image.SetPixel(x, y, color);
        }
    }

	image.WriteToFile("image.bmp");
}



// ===============================================
// ===============================================

void Juego::jugar() {

    this->crearBitmap();

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
            								this->jugadorEnTurno->getCantidadFichas(), this->jugadorEnTurno->getColor() );
            this->ponerFicha( jugadaActual );
            this->escribirFichaBitmap( jugadaActual[1][0], jugadaActual[1][1], jugadaActual[1][2] );
        }

        else {
            this->interfaz->tocaMoverFicha( this->jugadorEnTurno->getNombre(), this->jugadorEnTurno->getFicha()->getSimbolo(),
                                            this->jugadorEnTurno->getColor() );
            this->moverFicha( jugadaActual );
            this->borrarFichaBitmap( jugadaActual[0][0], jugadaActual[0][1], jugadaActual[0][2] );
            this->escribirFichaBitmap( jugadaActual[1][0], jugadaActual[1][1], jugadaActual[1][2] );
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


