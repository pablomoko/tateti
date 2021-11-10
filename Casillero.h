#ifndef _CASILLERO_H_INCLUDED_
#define _CASILLERO_H_INCLUDED_
#include "Ficha.h"

class Casillero{
private:
    Ficha * ficha;
    Casillero **** casillerosAdyacentes;

public:
    /*
     * Post: crea un Casillero con la Ficha vacia
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
     * Post: devuelve la Ficha del Casillero
     */
    Ficha * getFicha();

    /*
     * Post: establece la Ficha indicada en el Casillero
     */
    void setFicha(Ficha * nuevaFicha);
};

#endif