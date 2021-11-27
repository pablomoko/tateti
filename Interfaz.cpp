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

void Interfaz::mostrar(Ficha * ficha) {
    cout << ficha->getSimbolo();
}

void Interfaz::mostrar(Tablero * tableroActual) {
    unsigned int x = tableroActual->getDimensiones()[0];
    unsigned int y = tableroActual->getDimensiones()[1];
    unsigned int z = tableroActual->getDimensiones()[2];

    for (unsigned int k = 0; k < z; k++) {
        cout << "\nFichas en nivel z = " << z << endl;

        for (unsigned int j = 0; j < y; j++) {

            for (unsigned int i = 0; i < x; i++) {
                Casillero * casillero = tableroActual->getCasillero(i, j, k);
                cout << casillero->getFicha();  // Se imprimen todas las fichas de la línea
            }
            cout << "\n"; // Salto de línea para que la proxima vez que se impriman las fichas sean de la proxima columna
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
