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
};

#endif