#include "Interfaz.h"

void Interfaz::mostrarPantallaInicial() {
    cout << "      TATETI 2.0      " << endl;
    cout << "Bienvenido a Tateti 2.0, una version alternativa"
            "del Tateti convencional con un tablero en 3 dimensiones"
            "y varios jugadores y cartas para jugar!" << endl;
    cout << "\nProyecto desarrollado por alumnos de FIUBA" << endl;
}

void Interfaz::mostrarGanador(Jugador * ganador) {
    cout << "Juego terminado!\nGanador: " << ganador->getNombre() << endl;
}

void Interfaz::pedirCoordenadas() {
    cout << "Introduzca las 3 coordenadas donde desea colocar la ficha" << endl;
}

void Interfaz::mostrar(Tablero * tableroActual) {
    for (unsigned int k = 0; k < tableroActual->getDimensiones()[2]; k++) {
        for (unsigned int j = 0; j < tableroActual->getDimensiones()[1]; j++) {
            for (unsigned int i = 0; i < tableroActual->getDimensiones()[0]; i++) {

                Casillero * casillero = tableroActual->getCasillero(i, j, k);
                casillero->getFicha()
            }
        }
    }
}

void Interfaz::pedirNombre(int jugadorNumero) {
    cout << "Jugador " << jugadorNumero << " - Ingrese su nombre (max 10 caracteres): ";
}

void Interfaz::pedirCantidadJugadores() {
    cout << "Ingrese la cantidad de jugadores con la que desea jugar: ";
}

void Interfaz::pedirCantidadFichas() {
    cout << "Ingrese la cantidad de fichas que tendra cada jugador: ";
}

void Interfaz::ingresoInvalido() {
    cout << "El valor ingresado es invalido, vuelva a intentar" << endl;
}
