#ifndef __CARTA_H__
#define __CARTA_H__

#include <string>

class Carta {

private:
    unsigned int numero;
    std::string descripcion;


public:

    /* 
     * Pre: numero de carta entre 1 y 6, string con descripcion
     * Post: inicializa los atributos con los argumentos
     */
    Carta( unsigned int numeroDeCarta, std::string descripcion );


    /* 
     * Pre: -
     * Post: devuelve un entero entre 1 y 6
     */
    unsigned int getNumero();


    /* 
     * Pre: -
     * Post: devuelve string
     */
    std::string getDescripcion();

};


Carta::Carta( unsigned int numeroDeCarta, std::string descripcion ){
    this->numero = numeroDeCarta;
    this->descripcion = descripcion;
}


unsigned int Carta::getNumero() {

    return this->numero;
}


std::string Carta::getDescripcion() {

    return this->descripcion;
}


#endif //__CARTA_H__
