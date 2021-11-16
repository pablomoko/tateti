//
// Created by miguel on 16/11/21.
//

#ifndef TATETI_2_0_COLA_H
#define TATETI_2_0_COLA_H

#include "Nodo.h"

template<class T>
class Pila {

private:
    Nodo <T> * tope;
    unsigned int tamanio;

public:
    Pila();

    ~Pila();

    void push( T );

    T pop();

    bool estaVacia();

};


template<class T>
Pila<T>::Pila() {
    this->tope = NULL;
    this->tamanio = 0;
}


template<class T>
Pila<T>::~Pila() {

    while ( !(this->estaVacia()) ){
        this->pop();
    }
}


template<class T>
void Pila<T>::push(T dato) {
    Nodo<T> * nuevoNodo = new Nodo<T>(dato);
    if ( !this->tope ) {
        this->tope = nuevoNodo;
    }
    else {
        nuevoNodo->setSiguiente(this->tope);
        this->tope = nuevoNodo;
    }
    ++(this->tamanio);
}


template<class T>
T Pila<T>::pop() {
    if ( !(this->tope) ) {
        throw ("Pila vacia. No se puede desapilar");
    }
    T datoaBorrar = this->tope->getDato();
    Nodo<T> * nodoaBorrar = this->tope;
    this->tope = this->tope->getSiguiente();
    delete nodoaBorrar;
    return  datoaBorrar;
}

#endif //TATETI_2_0_COLA_H
