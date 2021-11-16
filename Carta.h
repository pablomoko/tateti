#ifndef __CARTA_H__
#define __CARTA_H__

class Carta {

private:
    unsigned int numero;

public:
    Carta( unsigned int numeroDeCarta );
    int getNumero();
};


Carta::Carta( unsigned int numeroDeCarta ){
    this->numero = numeroDeCarta;
}

int Carta::getNumero() {
    return this->numero;
}

#endif //__CARTA_H__
