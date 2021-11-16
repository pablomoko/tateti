#include "Ficha.h"
#include "Casillero.h"
#include "Jugador.h"


int main(){

    Ficha * ficha = NULL;

    try {
        ficha = new Ficha(' ');
    } catch(...) {    
    }

    if (ficha != NULL){
        delete ficha;
    }
    

    return 0;
}