#ifndef _CASILLERO_H_INCLUDED_
#define _CASILLERO_H_INCLUDED_
#include "Ficha.h"

const char VACIO = 'Z';





class Casillero{
private:
    Ficha * ficha;
    Casillero **** casillerosAdyacentes;
    Estado estado;


public:
    /*
     * Post: crea un Casillero con la Ficha vacia e inicializa
     * sus 27 casillerosAdyacentes
     */
    Casillero();

    /*
     * Post: crea un Casillero con la Ficha indicadas
     */
    Casillero(Ficha * ficha);

    /*
     * Post: libera toda la memoria solicitada para el Casillero
     */
    ~Casillero();

    /*
     * Pre: recibe las coordenadas respecto del mismo casillero tomando como referencia
     * que el origen es la posicion del casillero.
     * Post: asigna el casillero recibido como adyacente en la posicion recibida respecto
     * del mismo casillero. Lanza una excepcion si las coordenadas son inválidas
     */
    void asignarCasilleroAdyacente(int x, int y, int z, Casillero * casilleroAdyacente);

    /*
     * Post: devuelve la Ficha del Casillero
     */
    Ficha * getFicha();

    /*
     * Post: establece la Ficha indicada en el Casillero
     */
    void setFicha(Ficha * nuevaFicha);


    bool estaBloqueado();

    void bloquear();

    void desbloquear();
};

#endif