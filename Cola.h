#ifndef TATETI_2_0_COLA_H
#define TATETI_2_0_COLA_H

#include "Nodo.h"

template<class T>
class Cola {

private:
    Nodo <T> * inicio;
    Nodo <T> * final;
    unsigned int tamanio;

public:
    Cola();

    ~Cola();

    void push( T );

    T pop();

    bool estaVacia();

};


template<class T>
Cola<T>::Cola() {
    this->inicio = NULL;
    this->final = NULL;
    this->tamanio = 0;
}


template<class T>
Cola<T>::~Cola() {

    while ( !(this->estaVacia()) ){
        this->pop();
    }
}


template<class T>
void Cola<T>::push(T dato) {

    Nodo<T> * nuevoNodo = new Nodo<T>(dato);

    if ( !this->inicio ) {
        this->inicio = nuevoNodo;
        this->final = this->inicio
    }
    else {
        this->final->getSiguiente = nuevoNodo;
        this->final = nuevoNodo;
    }

    ++(this->tamanio);
}


template<class T>
T Cola<T>::pop() {

    if ( !(this->inicio) ) {
        throw ("Cola vacia. No se puede obtener elemento");
    }

    T datoaBorrar = this->inicio->getDato();
    Nodo<T> * nodoaBorrar = this->inicio;
    this->inicio = this->inicio->getSiguiente();
    delete nodoaBorrar;
    return  datoaBorrar;
}

#endif //TATETI_2_0_COLA_H
