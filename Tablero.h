#ifndef TATETI_2_0_TABLERO_H
#define TATETI_2_0_TABLERO_H

#include "Lista.h"
#include "Casillero.h"

class Tablero{
private:
    Lista<Lista<Casillero *> *> * casilleros;   //tablero de dos dimensiones con listas

public:
    /*
     * Pre: recibe las dimensiones con las que se desea crear el tablero
     * Post: inicializa un tablero de x ancho por y alto de casilleros vacios
     */
    Tablero(unsigned int x, unsigned int y);

    /*
     *
     */
    ~Tablero();

    /*
     * Pre: recibe las coordenadas x,y del casillero que se desea obtener
     * Post: devuelve el casillero que se encuentra en la coordenada recibida
     */
    Casillero * getCasillero(unsigned int x, unsigned int y);

    /*
     *
     */
    void setCasillero(unsigned int x, unsigned int y, Casillero * casillero)
};

#endif //TATETI_2_0_TABLERO_H
