#include "casillero.h"
#include "ficha.h"
using namespace std;

Casillero::Casillero(){
    ficha = nullptr;
}

Casillero::Casillero(Ficha * ficha){
    this->ficha = ficha;
}






