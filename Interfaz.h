#ifndef TATETI_2_0_INTERFAZ_H
#define TATETI_2_0_INTERFAZ_H

#include "iostream"
#include "Juego.h"

class Interfaz{
public:
    /*
     * Pre:
     * Post:
     */
    void mostrarPantallaInicial();

    /*
     * Pre:
     * Post:
     */
    void mostrarGanador();

    /*
     * Pre:
     * Post:
     */
    void mostrarControles();

    /*
     * Pre: recibe el estado actual del tablero
     * Post:
     */
    void mostrarTablero(Tablero * tableroActual);

    /*
     * Pre: recibe el numero de jugador al que corresponde el nombre
     * Post: pide por pantalla el nombre al jugador indicando su numero
     * ejemplo: Jugador 1: Tomas, Jugador 2: Miguel, ett
     */
    void pedirNombre(int jugadorNumero);
};

#endif //TATETI_2_0_INTERFAZ_H
