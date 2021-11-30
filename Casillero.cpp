#include "Casillero.h"

Casillero::Casillero(){
    this->ficha = new Ficha(VACIO);
    this->estado = CASILLERO_DESBLOQUEADO;

    this->casillerosAdyacentes = new Casillero *** [3];
    for (int i = 0; i < 3; i++) {
        this->casillerosAdyacentes[i] = new Casillero ** [3];
        for (int j = 0; j < 3; j++) {
            this->casillerosAdyacentes[i][j] = new Casillero * [3];
        }
    }
}

Casillero::Casillero(Ficha * nuevaFicha){

    this->ficha = nuevaFicha;
    this->estado = CASILLERO_DESBLOQUEADO;

    this->casillerosAdyacentes = new Casillero *** [3];
    for (int i = 0; i < 3; i++) {
        this->casillerosAdyacentes[i] = new Casillero ** [3];
        for (int j = 0; j < 3; j++) {
            this->casillerosAdyacentes[i][j] = new Casillero * [3];
        }
    }
}

Casillero::~Casillero() {

    if ( this->ficha ) {
        delete this->ficha;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete[] this->casillerosAdyacentes[i][j];
        }
        delete[] this->casillerosAdyacentes[i];
    }
    delete[] this->casillerosAdyacentes;
}

void Casillero::asignarCasilleroAdyacente(int x, int y, int z, Casillero * casilleroAdyacente) {
    if ((x < -1 || x > 1) || (y < -1 || y > 1) || (z < -1 || z > 1)){
        throw "Coordenadas invalidas. Se toma el mismo casillero como origen por lo tanto"
              "las coordenadas deben estan comprendidas entre -1 y 1";
    }

    // matriz con indices negativos ?????
    // agrego +1
    this->casillerosAdyacentes[x+1][y+1][z+1] = casilleroAdyacente;
}

bool Casillero::tieneAdyacente(unsigned int x, unsigned int y, unsigned int z) {
    //Puede que este mal
    return (this->casillerosAdyacentes[x][y][z] != NULL);
}

bool Casillero::esAdyacente( Casillero * casillero ){

    Casillero * ca;
    for (int k = 0; k < 3; ++k) {
        for (int j = 0; j < 3; ++j) {
            for (int i = 0; i < 3; ++i) {
                ca = this->getAdyacente(i, j, k);
                if (ca == casillero) {
                    return true;
                }
            }
        }
    }
    return false;
}

Casillero * Casillero::getAdyacente(unsigned int i, unsigned int j, unsigned int k) {
    Casillero * c = this->casillerosAdyacentes[i][j][k];
    return c;
}

// probar compilar esta funcion
unsigned int Casillero::getLongitudFichasIguales(unsigned int i, unsigned int j, unsigned int k){
    //Pensar otro algoritmo sin tantos returns
    if (!this->tieneAdyacente(i, j, k) ||  //Caso base
        !this->ficha ||
        this->ficha->getSimbolo() == VACIO ||
        ( i==1 && j==1 && k==1 ) ){
        return 0;
    }


    Casillero * casilleroAdyacente = this->getAdyacente(i, j, k);

    if (this->tienenMismaFicha(casilleroAdyacente)){
        return (1 + casilleroAdyacente->getLongitudFichasIguales(i, j, k));
    }
    //Las fichas son distintas y la longitud de fichas iguales es 0
    return 0;
}

Ficha * Casillero::getFicha(){
    return this->ficha;
}

void Casillero::setFicha(Ficha * nuevaFicha) {
    if( !this->estaVacio() || this->estaBloqueado() ) {
        throw("No se puede poner una ficha en el casillero ocupado o bloqueado");
    }
    if ( this->ficha ) delete this->ficha;
    this->ficha = new Ficha(nuevaFicha);
}

Ficha * Casillero::quitarFicha() {

    if ( this->ficha == NULL ) {
        throw("No hay ficha para quitar");
    }
    Ficha * ficha = this->ficha;
    this->ficha = new Ficha(VACIO);
    return ficha;
}

bool Casillero::estaBloqueado() {
    return (this->estado == CASILLERO_BLOQUEADO);
}

void Casillero::bloquear() {
    this->estado = CASILLERO_BLOQUEADO;
}

void Casillero::desbloquear() {
    this->estado = CASILLERO_DESBLOQUEADO;
}


bool Casillero::tienenMismaFicha( Casillero * casilleroAdyacente ) {

    try {
        return ( this->ficha->esIgual( casilleroAdyacente->getFicha() ) );
    }
    catch (...) {
        return false;
    }
}



bool Casillero::estaVacio() {

    if ( this->ficha->getSimbolo() == VACIO ) {
        return true;
    }

    return false;
}
