#ifndef __CARTA_H__
#define __CARTA_H__

#include <string>
#include "constantes.h"


class Carta {

private:
    funcion_t funcion;


public:

    /* 
     * Pre: numero de carta entre 1 y 6, string con descripcion
     * Post: inicializa los atributos con los argumentos
     */
    Carta( funcion_t funcion );


    /* 
     * Pre: -
     * Post: devuelve un entero entre 1 y 6
     */
    funcion_t getFuncionalidad();


    /* 
     * Pre: -
     * Post: devuelve string
     */
    std::string getDescripcion();

};


Carta::Carta( funcion_t funcion ){

    this->funcion = funcion;
}


funcion_t Carta::getFuncionalidad() {

    return this->funcion;
}


std::string Carta::getDescripcion() {

    return funcionalidades[this->funcion];
}


#endif //__CARTA_H__
