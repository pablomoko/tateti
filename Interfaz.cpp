#include "Interfaz.h"

void Interfaz::mostrarPantallaInicial() {
    cout << "      TATETI 2.0      " << endl;
    cout << "Bienvenido a Tateti 2.0, una version alternativa"
            "del Tateti convencional con un tablero en 3 dimensiones"
            "y varios jugadores y cartas para jugar!" << endl;
    cout << "\nProyecto desarrollado por alumnos de FIUBA" << endl;
}

void Interfaz::mostrar(Ficha * ficha) {
    cout << ficha->getSimbolo();
    
}

void Interfaz::mostrarGanador(std::string nombreGanador) {
    std::cout << "\nEl ganador del juego es: " << nombreGanador<<std::endl;
}

void Interfaz::mostrarControles() {

}

void Interfaz::mostrarTablero(Tablero * t) {

    int dim[3];
    dim[0] = t->getDimensiones()[0];
    dim[1] = t->getDimensiones()[1];
    dim[2] = t->getDimensiones()[2];

    std::cout<<"\n\nTABLERO:\n\n";
    for ( int k=0; k < dim[2]; ++k ) {
        std::cout<<"Profundo:"<<k<<"\n";
        for ( int j=0; j < dim[1]; ++j ) {
            std::cout<<"alto:"<<j<<"    ";

            for ( int i=0; i < dim[0]; ++i ) {
                char simbolo = t->getCasillero(i, j, k)->getFicha()->getSimbolo();
                if ( simbolo != VACIO ) {
                    std::cout<<" "<<simbolo<<"";
                }
                else {
                    std::cout<<" "<<"-";
                }
            }
            std::cout<<"\n";
        }
        std::cout<<"\n\n";
    }

}


void Interfaz::pedirNombre(int jugadorNumero) {
    std::cout << "\nJugador " << jugadorNumero << " - Ingrese su nombre (max 10 caracteres): ";
}


void Interfaz::pedirCantidadJugadores() {
    std::cout << "\nIngrese la cantidad de jugadores con la que desea jugar (2 o mas): ";
}


void Interfaz::pedirCantidadFichas() {
    std::cout << "\nIngrese la cantidad de fichas que tendra cada jugador (3 o mas): ";
}


void Interfaz::pedirDimensiones() {
    std::cout << "\nIngrese las dimensiones del tablero (ancho, alto, profundo): " << std::endl;
}


void Interfaz::pedirCantidadCartas() {
    std::cout << "\nIngrese la cantidad maxima de cartas que podra tener en la mano cada jugador al mismo tiempo (minimo 1): ";
}


void Interfaz::pedirPosicionFichaABloquear() {
    std::cout << "\nIngrese la posicion en el tablero de la ficha a bloquear: " << std::endl;
}


void Interfaz::informarNoHayFicha() {
    std::cout << "\nNo hay una ficha en la posicion del tablero ingresada." << std::endl;
}


void Interfaz::pedirPosicionCasilleroABloquear() {
    std::cout << "\nIngrese la posicion en el tablero del casillero a bloquear: " << std::endl;
}


void Interfaz::ingresoInvalido() {
    std::cout << "\nEl valor ingresado es invalido, vuelva a intentar" << std::endl;
}


void Interfaz::pedirCoordPonerFicha() {
    std::cout << "\nIngrese la posicion en el tablero donde desea colocar su ficha: " << std::endl;
}


void Interfaz::informarCasilleroNoDisponible() {
    std::cout << "\nEl casillero elegido no esta disponible" << std::endl;
}


void Interfaz::pedirCoordOrigenMoverFicha() {
    std::cout << "\nIngrese la posicion en el tablero de la ficha que desea mover: " << std::endl;
}


void Interfaz::pedirCoordDestinoMoverFicha() {
    std::cout << "\nIngrese la posicion en el tablero a donde desea mover la ficha elegida: " << std::endl;
}


void Interfaz::preguntarUsarCarta() {
    std::cout << "\nQuieres utilizar una carta? (S/N): " ;
}


void Interfaz::preguntarNroCarta() {
    std::cout << "\nCual carta quieres usar? (1 a 6): " ;
}


void Interfaz::tocaPonerFicha(std::string nombreJugador) {
    std::cout << "Jugador: "<< nombreJugador<<" te toca poner una ficha." << std::endl;
}


void Interfaz::tocaMoverFicha(std::string nombreJugador) {
    std::cout << "Jugador: "<< nombreJugador<<" te toca mover una ficha." << std::endl;
}


void Interfaz::mostrarCartasJugador(Lista<Carta*> * cartas) {
    std::cout << "\nTus cartas son: ";
    cartas->iniciarCursor();
    while ( cartas->avanzarCursor() ) {
        Carta * carta = cartas->obtenerCursor();
        std::cout << "\n\t"<<carta->getFuncionalidad()+1<<" : "<<carta->getDescripcion();
    }
}


void Interfaz::jugadorSinCartas() {
    std::cout << "\nNo tienes cartas para usar." << std::endl;
}

