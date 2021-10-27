#ifndef _CASILLERO_H_INCLUDED_
#define _CASILLERO_H_INCLUDED_
#include "Ficha.h"

class Casillero
{
friend class Ficha;
private:
    Ficha *ficha;
public:
    Casillero();//CONSTRUCTOR POR DEFECTO
    ~Casillero();//DESTRUCTOR
    Casillero(Ficha * ficha);//CONSTRUCTOR PARAMETRIZADO

    /*
     * Post: devuelve la ficha del casillero
     */
    Ficha * getFicha();

    /*
     * Post: establece la ficha indicada en el casillero
     */
    void setFicha(Ficha * nuevaFicha);
};

#endif