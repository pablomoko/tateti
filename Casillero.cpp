#include "Casillero.h"
using namespace std;

Casillero::Casillero(){
    this->ficha = new Ficha(VACIO); //definir VACIO
}

Casillero::Casillero(Ficha * ficha){
    this->ficha = ficha;
}

void Casillero::~Casillero() {
    
}

Ficha * Casillero::getFicha(){
    return this->ficha;
}

void Casillero::setFicha(Ficha * nuevaFicha){
    this->ficha = nuevaFicha;




