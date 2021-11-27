#ifndef TATETI_2_0_INTERFAZ_H
#define TATETI_2_0_INTERFAZ_H

#include "iostream"
#include "Juego.h"

using namespace std;

class Interfaz{
public:
    /*
     * Post: muestra por pantalla el menu principal del juego mostrando el titulo
     * del mismo y dando bienvenida al usuario
     */
    void mostrarPantallaInicial();

    /*
     * Pre: recibe el Jugador no nulo que ha ganado el juego
     * Post: muestra un mensaje por pantalla indicando el nombre del ganador
     */
    void mostrarGanador(Jugador * ganador);

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
     * Pre: recibe el número de jugador al que corresponde el nombre
     * Post: pide por pantalla el nombre al jugador indicando su número
     * ejemplo: Jugador 1: Tomás, Jugador 2: Miguel, ett
     */
    void pedirNombre(int jugadorNumero);

    /*
     * Post: pide por pantalla la cantidad de Jugadores que tendra el Juego
     */
    void pedirCantidadJugadores();

    /*
     * Post: pide por pantalla la cantidad de Fichas que tendra cada Jugador
     */
    void pedirCantidadFichas();

    /*
     * Post: muestra un mensaje por pantalla diciendo que se ingresó un valor invalido y pide
     * que se ingrese nuevamente
     */
    void ingresoInvalido();
};

#endif //TATETI_2_0_INTERFAZ_H
