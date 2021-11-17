#ifndef __CARTA_H__
#define __CARTA_H__

#include <string>

class Carta {

private:
    unsigned int numero;
    std::string descripcion;

public:
    Carta( unsigned int numeroDeCarta, std::string descripcion );
    unsigned int getNumero();
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
