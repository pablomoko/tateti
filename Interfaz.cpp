#include "Interfaz.h"

void Interfaz::mostrarPantallaInicial() {
    cout << "      TATETI 2.0      " << endl;
    cout << "Bienvenido a Tateti 2.0, una version alternativa"
            "del Tateti convencional con un tablero en 3 dimensiones"
            "y varios jugadores y cartas para jugar!" << endl;
    cout << "\nProyecto desarrollado por alumnos de FIUBA" << endl;
}

void Interfaz::mostrarGanador() {

}

void Interfaz::mostrarControles() {

}

void Interfaz::mostrarTablero(Tablero * tableroActual) {

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
