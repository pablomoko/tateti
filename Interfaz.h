#ifndef INTERFAZ_H_
#define INTERFAZ_H_


#include "iostream"
#include "Juego.h"
#include "Tablero.h"
#include "Carta.h"
#include "Lista.h"

using namespace std;


class Interfaz{
public:

    /*
     * Post: muestra por pantalla el menu principal del juego mostrando el titulo
     * del mismo y dando bienvenida al usuario
     */
    void mostrarPantallaInicial();

    /*
     * Post: muestra en pantalla el simbolo de la ficha recibida sin dar
     * salto de línea al final
     */
    void mostrar(Ficha * ficha);


    /*
     * Pre: recibe un string con el nombre del Jugador que ha ganado el juego
     * Post: muestra un mensaje por pantalla indicando el nombre del ganador
     */
    void mostrarGanador(std::string nombreGanador);

    /*
     * Pre:
     * Post:
     */
    void mostrarControles();

    /*
     * Pre: recibe el estado actual del tablero
     * Post: muestra por pantalla las Fichas de los casilleros del tablero recibido
     * imprimiendo tantos planos como profundidad tenga el tablero recibido.
     * Por ejemplo si el tablero tiene una profundidad de 2 niveles (z=2)
     * se mostrara por pantalla 2 planos xy pertenecientes a cada nivel de profundidad
     */
    void mostrarTablero(Tablero * );

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
     * Post:
     */
    void pedirDimensiones();

    /*
     * Post:
     */
    void pedirCantidadCartas();

    /*
     *
     */
    void pedirPosicionFichaABloquear();


    /*
     *
     */
    void informarNoHayFicha();


    void pedirPosicionCasilleroABloquear();


    /*
     * Post: indica por pantalla que se ingreso un valor invalido 
     */
    void ingresoInvalido();


    /*
     * Post: muestra un mensaje en pantalla pidiendo al jugador que introduzca
     * las 3 coordenadas del tablero donde desea ubicar su ficha
     */
    void pedirCoordPonerFicha();


    /*
     *
     */
    void informarCasilleroNoDisponible();


    /*
     *
     */
    void pedirCoordOrigenMoverFicha();


    /*
     *
     */
    void pedirCoordDestinoMoverFicha();


    /*
     *
     */
    void preguntarUsarCarta();


    /*
     *
     */
    void preguntarNroCarta();


    void tocaPonerFicha(std::string);


    void tocaMoverFicha(std::string);


    /*
     *
     */
    void mostrarCartasJugador(Lista<Carta*> *);


    /*
     *
     */
    void jugadorSinCartas();
};




#endif /* INTERFAZ_H_ */