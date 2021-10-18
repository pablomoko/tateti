#include "ficha.h"
#include "casillero.h"
#include "jugador.h"


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