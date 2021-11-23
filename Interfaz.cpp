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
    std::cout << "Jugador " << jugadorNumero << " - Ingrese su nombre (max 10 caracteres): ";
}

void Interfaz::pedirCantidadJugadores() {
    std::cout << "Ingrese la cantidad de jugadores con la que desea jugar: ";
}

void Interfaz::ingresoInvalido() {
    std::cout << "El valor ingresado es invalido, vuelva a intentar" << std::endl;
}
