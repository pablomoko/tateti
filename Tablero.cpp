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

void Tablero::setCasillero(unsigned int x, unsigned int y, Ficha *ficha) {
    this->casilleros->obtener(x)->obtener(y)->setFicha(ficha);
}
