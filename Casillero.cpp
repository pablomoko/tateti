#include "Casillero.h"

Casillero::Casillero(){
    // se crean en 'z', cambiarlo
    this->ficha = new Ficha('z');

    this->casillerosAdyacentes = new Casillero *** [3];
    for (int i = 0; i < 3; i++) {
        this->casillerosAdyacentes[i] = new Casillero ** [3];
        for (int j = 0; j < 3; j++) {
            this->casillerosAdyacentes[i][j] = new Casillero * [3];
        }
    }
    this->estado = DESBLOQUEADO;
}

Casillero::Casillero(Ficha * ficha){
    this->ficha = ficha;
}

Casillero::~Casillero() {
    delete this->ficha;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete[] this->casillerosAdyacentes[i][j];
        }
        delete[] this->casillerosAdyacentes[i];
    }
    delete[] this->casillerosAdyacentes;
    //this->casillerosAdyacentes = NULL;   hace falta ????
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

Casillero * Casillero::getAdyacente(unsigned int i, unsigned int j, unsigned int k) {
    return this->casillerosAdyacentes[i][j][k];
}

// probar compilar esta funcion
unsigned int Casillero::getLongitudFichasIguales(unsigned int i, unsigned int j, unsigned int k){
    //Pensar otro algoritmo sin tantos returns
    if (!this->tieneAdyacente(i, j, k) ||  //Caso base
        !this->estaOcupado(i, j, k)){
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
    this->ficha = nuevaFicha;
}

bool Casillero::estaBloqueado() {
    return (this->estado == BLOQUEADO);
}

void Casillero::bloquear() {
    this->estado = BLOQUEADO;
}

void Casillero::desbloquear() {
    this->estado = DESBLOQUEADO;
}
