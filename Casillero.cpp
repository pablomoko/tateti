#include "Casillero.h"
using namespace std;

Casillero::Casillero(){

    this->ficha = new Ficha(VACIO); //definir VACIO

    this->casillerosAdyacentes = new Casillero *** [3];
    for (int i = 0; i < 3; ++i) {
        this->casillerosAdyacentes[i] = new Casillero ** [3];

        for (int j = 0; j < 3; ++j) {
            this->casillerosAdyacentes[i][j] = new Casillero * [3];
        }
    }

    this->estado = desbloqueado;
}


Casillero::Casillero(Ficha * ficha){
    this->ficha = ficha;
}


Casillero::~Casillero() {
    
}


void Casillero::asignarCasilleroAdyacente(int x, int y, int z, Casillero * casilleroAdyacente) {
    if ((x < -1 || x > 2) || (y < -1 || y > 2) || (z < -1 || z > 2)){
        throw "Coordenadas invalidas. Se coma el mismo casillero como origen por lo tanto"
              "las coordenadas deben estan comprendidas entre -1 y 2";
    }

    this->casillerosAdyacentes[x][y][z] = casilleroAdyacente;
}


Ficha * Casillero::getFicha(){
    return this->ficha;
}


void Casillero::setFicha(Ficha * nuevaFicha) {
    this->ficha = nuevaFicha;
}


bool Casillero::estaBloqueado() {

    return (this->estado == bloqueado);
}


void Casillero::bloquear() {

    this->estado = bloqueado;
}


void Casillero::desbloquear() {

    this->estado = desbloqueado;
}