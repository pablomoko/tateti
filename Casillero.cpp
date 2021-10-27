#include "Casillero.h"
#include "Ficha.h"
using namespace std;

Casillero::Casillero(){
    ficha = nullptr;
}

Casillero::Casillero(Ficha * ficha){
    this->ficha = ficha;
}

Ficha * Casillero::getFicha(){
    return this->ficha;
}

void Casillero::setFicha(Ficha * nuevaFicha){
    this->ficha = nuevaFicha;




