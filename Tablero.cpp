#include "Tablero.h"

Tablero::Tablero(unsigned int x, unsigned int y, unsigned int z) {

    this->dimensiones[0] = x;
    this->dimensiones[1] = y;
    this->dimensiones[2] = z;

    //Se crea el tablero
    this->casilleros = new Lista<Lista<Lista<Casillero *> *> *>();

    for (int k = 0; k < z; k++) {   //Se crea la lista perteneciente a las filas del tablero
        Lista<Lista<Casillero *> *> * fila = new Lista<Lista<Casillero *> *>();

        for (int i = 0; i < x; i++) {   //Se crea la lista perteneciente a las columnas del plano x,y
            Lista<Casillero *> * columna = new Lista<Casillero *>();

            for (int j = 0; j < y; j++) {   //Se crean los casilleros apuntados por cada columna del plano
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
                Casillero * casillero = this->getCasillero(x, y, z);
                //pensar mejor disenio y evitar codigo flecha
                for (int l = -1; l < 2; l++) {
                    for (int m = -1; m < 2; m++) {
                        for (int n = -1; n < 2; n++) {  //Itera matriz con origen en casillero
                            if (existeCasillero(i+l, j+m, k+n)) {
                                Casillero *casilleroAdyacente = this->getCasillero(i+l, j+m, k+n);
                                casillero->asignarCasilleroAdyacente(l, m, n, casilleroAdyacente);
                            }
                        }
                    }
                }
            }
        }
    }
}

Tablero::~Tablero() {

}


int * Tablero::getDimensiones() {

    return this->dimensiones;
}


bool Tablero::existeCasillero(unsigned int x, unsigned int y, unsigned int z) {
    
}

bool Tablero::hayTateti(Casillero * casilleroOrigen){

    casilleroOrigen->getCasillerosAdyacentes(); //que hace esto
    int longitudesAdyacentes[3][3][3];  //Cambiar por un nombre más explicito
    //En esta iteracion se guardan la cantidad de casilleros con fichas iguales en cada direccion
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                /*
                 * Se guarda la longitud de un vector con origen en casilleroOrigen
                 * en la posicion del array correspondiente a cada iteracion
                 */
                longitudesAdyacentes[i][j][k] = casilleroOrigen->getLongitudFichasIguales(i, j, k);
            }
        }
    }

    /*
     * Una vez tenemos la cantidad de fichas iguales en cada direccion respecto de casilleroOrigen,
     * se checkea si en alguna direccion hay 3 y en caso de que si se devuelve true
     */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if ((longitudesAdyacentes[i][j][k] + 1 == 3)||    //Caso tateti siguiendo una direccion
                    (longitudesAdyacentes[i][j][k] + longitudesAdyacentes[2-i][2-j][2-k] == 3)){   //Caso tateti en un adyacente y su opuesto
                    return true
                }
            }
        }
    }

    return false
}

Casillero * Tablero::getCasillero(unsigned int x, unsigned int y, unsigned int z) {
    
    return this->casilleros->obtener(z)->obtener(x)->obtener(y);
}


void Tablero::setCasillero(unsigned int x, unsigned int y, unsigned int z, Ficha * ficha) {
    this->casilleros->obtener(z)->obtener(x)->obtener(y)->setFicha(ficha);
}


void Tablero::moverFicha(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int x2, unsigned int y2, unsigned int z2) {
    //Valida si las coordenadas ingresadas son válidas
    if(x1 > casilleros->contarElementos() ||
       x2 > casilleros->contarElementos() ||
       y1 > casilleros->obtener(1)->contarElementos() ||  //La posicion escogida es arbitraria, ya que el tablero es cuadrado
       y2 > casilleros->obtener(1)->contarElementos()){
        throw "Una de las coordenadas ingresadas esta fuera de los limites del tablero";
    }

    //Intercambia fichas, se podría implementar usando anterior y siguiente?
    Ficha * ficha1 = casilleros->obtener(x1)->obtener(y1)->obtener(z1)->getFicha();
    Ficha * ficha2 = casilleros->obtener(x2)->obtener(y2)->obtener(z2)->getFicha();
    casilleros->obtener(x2)->obtener(y2)->obtener(z1)->setFicha(ficha1);
    casilleros->obtener(x1)->obtener(y1)->obtener(z1)->setFicha(ficha2);
}
