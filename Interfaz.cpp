#include "Interfaz.h"

void Interfaz::mostrarPantallaInicial() {

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
