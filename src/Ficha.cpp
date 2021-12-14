#include "Ficha.h"
#include <string>

Ficha::Ficha(char simbolo, RGBApixel color){
    this->validar(simbolo);
    this->simbolo = simbolo;
    this->estado = FICHA_DESBLOQUEADA;
    this->color = color;
}


Ficha::Ficha(Ficha* ficha) {
    this->simbolo = ficha->getSimbolo();
    this->estado = FICHA_DESBLOQUEADA;
    this->color = ficha->color;
}


Ficha::~Ficha() {

}


char Ficha::getSimbolo() {
    return this->simbolo;
}


void Ficha::validar(char simbolo){
    if ((simbolo == '\0') ||
        (simbolo == ' ')) {
        std::string error = "Simbolo ingresado invalido. '" +  simbolo ;
        throw  error + "' " ;
    }
}


bool Ficha::esIgual(Ficha * ficha2){
    try {
        return (this->getSimbolo() == ficha2->getSimbolo());
    } catch (...) {
        //si los punteros son nulos salta la excepcion
        return false;
    }
}


bool Ficha::estaBloqueada() {

    return (this->estado == FICHA_BLOQUEADA);
}


void Ficha::bloquear() {

    this->estado = FICHA_BLOQUEADA;
}


void Ficha::desbloquear() {

    this->estado = FICHA_DESBLOQUEADA;
}


RGBApixel Ficha::getColor() {
    return this->color;
}