#include "Tablero.h"

Tablero::Tablero(unsigned int x, unsigned int y) {
    this->casilleros = new Lista<Lista<Casillero *> *>();

    for (int i = 0; i < x; i++) {   //Se crea la lista perteneciente a las columnas
        Lista<Casillero *> * columna = new Lista<Casillero *>();

        for (int j = 0; j < y; ++j) {   //Se crean los casilleros apuntados por cada columna
            Casillero * casillero = new Casillero();
            columna->altaFinal(casillero)
        }
        //Una vez creadas las columnas con sus respectivos casilleros, son agregadas al tablero
        this->casilleros->altaFinal(columna);
    }
}

Tablero::~Tablero() {

}

Casillero * Tablero::getCasillero(unsigned int x, unsigned int y) {
    return this->casilleros->obtener(x)->obtener(y);
}

void Tablero::setCasillero(unsigned int x, unsigned int y, Ficha * ficha) {
    this->casilleros->obtener(x)->obtener(y)->setFicha(ficha);
}

void Tablero::moverFicha(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
    //Valida si las coordenadas ingresadas son válidas
    if(x1 > casilleros->contarElementos() ||
       x2 > casilleros->contarElementos() ||
       y1 > casilleros->obtener(1)->contarElementos() ||  //La posicion escogida es arbitraria, ya que el tablero es cuadrado
       y2 > casilleros->obtener(1)->contarElementos()){
        throw "Una de las coordenadas ingresadas esta fuera de los limites del tablero"
    }

    //Intercambia fichas, se podría implementar usando anterior y siguiente?
    Ficha * ficha1 = casilleros->obtener(x1)->obtener(y1)->getFicha();
    Ficha * ficha2 = casilleros->obtener(x2)->obtener(y2)->getFicha();
    casilleros->obtener(x2)->obtener(y2)->setFicha(ficha1);
    casilleros->obtener(x1)->obtener(y1)->setFicha(ficha2);
}
