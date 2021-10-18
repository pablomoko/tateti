#include "jugador.h"
using namespace std;


Jugador::Jugador(std::string nombreJugador,Ficha * fichas,int cantidadFichas){
    this->nombreJugador= nombreJugador;
    this->fichas = fichas;
    this->cantidadFichas = cantidadFichas;
}


size_t Jugador::getCantidadFichas() const{
    return cantidadFichas;
}

void Jugador::disminuirCantidadFichas(){
    cantidadFichas--;
}




