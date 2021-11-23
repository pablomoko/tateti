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
     * Pre:
     * Post:
     */
    void pedirNombre(int jugadorNumero);
};

#endif //TATETI_2_0_INTERFAZ_H
