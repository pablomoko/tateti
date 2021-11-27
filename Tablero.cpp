#include "Tablero.h"

Tablero::Tablero(unsigned int x, unsigned int y, unsigned int z) {

    this->dimensiones[0] = x;
    this->dimensiones[1] = y;
    this->dimensiones[2] = z;

    //Se crea el tablero
    this->casilleros = new Lista<Lista<Lista<Casillero *> *> *>();

    for (unsigned int k = 0; k < z; k++) {   //Se crea la lista perteneciente a las filas del tablero
        Lista<Lista<Casillero *> *> * fila = new Lista<Lista<Casillero *> *>();

        for (unsigned int j = 0; j < y; j++) {   //Se crea la lista perteneciente a las columnas del plano x,y
            Lista<Casillero *> * columna = new Lista<Casillero *>();

            for (unsigned int i = 0; i < x; i++) {   //Se crean los casilleros apuntados por cada columna del plano
                Casillero * casillero = new Casillero();
                columna->altaFinal(casillero);
            }
            //Una vez creadas las columnas del plano, se agregan a la lista de columnas que luego representara una fila del trablero
            fila->altaFinal(columna);
        }
        //Cada vez que el primer for ejecuta su bloque, se le agrega un plano de *Casillero al tablero en el nivel k
        this->casilleros->altaFinal(fila);
    }

    //Con el tablero ya creado, se asignan los vecinos de los casilleros
    for (int k = 0; k < z; k++) {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {   //Itera los casilleros del tablero uno por uno
                Casillero * casillero = this->getCasillero(i, j, k);
                //pensar mejor disenio y evitar codigo flecha
                for (int l = -1; l < 2; l++) {
                    for (int m = -1; m < 2; m++) {
                        for (int n = -1; n < 2; n++) {  //Itera matriz con origen en casillero
                            if (this->existeCasillero(i+l, j+m, k+n)) {
                                Casillero *casilleroAdyacente = this->getCasillero(i+l, j+m, k+n);
                                casillero->asignarCasilleroAdyacente(l, m, n, casilleroAdyacente);
                            } else {
                                casillero->asignarCasilleroAdyacente(l, m, n, NULL);
                            }
                        }
                    }
                }
            }
        }
    }
}

Tablero::~Tablero() {
    //liberar lista de lista de lista de casilleros
    // todos los indices con +1 por la funcion obtener() !!!
    for(int k = 0; k < this->dimensiones[0]; k++) {
        for(int j = 0; j < this->dimensiones[0]; j++) {
            for(int i = 0; i < this->dimensiones[0]; i++) {
                delete this->getCasillero(i, j, k);
            }
            delete this->casilleros->obtener(k+1)->obtener(j+1);
        }
        delete this->casilleros->obtener(k+1);
    }
    delete this->casilleros;
    //this->casilleros = NULL;  hace falta   ???
}

int * Tablero::getDimensiones() {
    return this->dimensiones;
}

bool Tablero::existeCasillero(int x, int y, int z) {
    return (x >= 0 && x < this->getDimensiones()[0] &&
            y >= 0 && y < this->getDimensiones()[1] &&
            z >=0 && z < this->getDimensiones()[2]);
}

Casillero * Tablero::getCasillero(unsigned int x, unsigned int y, unsigned int z) {
    // habria que agregar alguna validacion ?????
    // sumo uno porque obtener va del [1, contarElementos()]
    // indice desde 0  o  indice desde 1 ??????
    return this->casilleros->obtener(z+1)->obtener(y+1)->obtener(x+1);
}

void Tablero::setCasillero(unsigned int x, unsigned int y, unsigned int z, Ficha * ficha) {
    // Validar ???
    // Hacer un throw catch ???
    // de nuevo corrijo indices de funcion obtener
    this->casilleros->obtener(z+1)->obtener(y+1)->obtener(x+1)->setFicha(ficha);
}
