#ifndef _JUGADOR_H_INCLUDED_
#define _JUGADOR_H_INCLUDED_
#include <iostream>
#include "Ficha.h"

class Jugador
{
friend class Ficha;
private:
    std::string nombreJugador;
    Ficha * fichas;
    int cantidadFichas;
public:  
        Jugador(std::string nombreJugador,Ficha * fichas,int cantidadFichas);
        ~Jugador();
        size_t getCantidadFichas() const;
        void disminuirCantidadFichas();
};

#endif