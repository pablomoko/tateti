#include "Ficha.h"
#include <iostream>
#include <string>

Ficha::Ficha(char simbolo){
    this->validar(simbolo);
    this->simbolo = simbolo;
}

Ficha::~Ficha(){}

void Ficha::validar(char simbolo){
    if ((simbolo == '\0') || 
        (simbolo == ' ')) {
        std::string error = "Simbolo ingresado invalido. '" +  simbolo ;
        throw  error + "' " ;
    }    
}





