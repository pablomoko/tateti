#ifndef TATETI_2_0_TABLERO_H
#define TATETI_2_0_TABLERO_H

#include "Lista.h"
#include "Casillero.h"
#include "Ficha.h"

class Tablero{
private:
    Lista<Lista<Lista<Casillero *> *> *> * casilleros;
    int dimensiones[3];

public:
    /*
     * Pre: recibe las longitudes de las tres dimensiones con las que se desea crear el tablero
     * Post: inicializa un tablero de x ancho, y alto, z profundidad de casilleros vacios y
     * asigna sus respectivos casilleros adyacentes
     */
    Tablero(unsigned int x, unsigned int y, unsigned int z);

    /*
     * Post: libera la memoria solicitada para la creacion del tablero
     */
    ~Tablero();

    /*
     * Post: devuelve un puntero a las dimensiones del Tablero
     */
    int * getDimensiones();

    /*
     * Pre: recibe las coordenadas x,y,z del Casillero que se desea verificar
     * Post: devuelve true si existe un Casillero en el Tablero ubicado en las
     * coordenadas recibidas, devuelve false si no existe y lanza una excepcion
     * si las coordenadas son inválidas
     */
    bool existeCasillero(unsigned int x, unsigned int y, unsigned int z);

    /*
     * Pre: recibe el casillero donde se desea checkear y hay tateti o no
     * Post: devuelve en booleano si hay tateti o no en la posicion del
     * Casillero recibida. Hay tateti cuando hay 3 casilleros adyacentes
     * con el mismo tipo de ficha
     */
    bool hayTateti(Casillero * casilleroOrigen);

    /*
     * Pre: recibe las coordenadas x,y,z del casillero que se desea obtener
     * Post: devuelve el casillero que se encuentra en la coordenada recibida
     */
    Casillero * getCasillero(unsigned int x, unsigned int y, unsigned int z);

    /*
     * Pre: recibe las coordenadas x,y,z donde se desea colocar la ficha pasada como argumento
     * Post: se coloca la ficha recibida en el casillero de la coordenada indicada
     */
    void setCasillero(unsigned int x, unsigned int y, unsigned int z, Ficha * ficha);

    /*
     * Pre: recibe dos coordenadas pertenecientes al tablero. Las primeras indican cual
     * ficha mover y las segundas hacia donde. El movimiento debe ser adyacente
     *
     * Post: intercambia la ficha del casillero ubicado en la primer coordenada con el de la segunda
     * si las coordenadas son inválidas lanza una excepcion
     */
    void moverFicha(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int x2, unsigned int y2, unsigned int z2);
};

#endif //TATETI_2_0_TABLERO_H
