#ifndef TATETI_2_0_LISTA_H
#define TATETI_2_0_LISTA_H

#include "Nodo.h"

template<class T> class Lista {
private:
    Nodo <T> * primero;
    unsigned int tamanio;
    Nodo<T> * cursor;

public:
    /*
     * Post: constructor de lista vacia
     */
    Lista();

    /*
     * Post: copia la lista recibida
     */
    Lista(Lista<T> &otraLista);

    /*
     * Post: libera los recursos asociados a la lista
     */
    ~Lista();

    /*
     * Post: agrega elemento al final de Lista (posición contarElementos() + 1)
     */
    void altaFinal(T elemento);

    /*
     * Pre: posición pertenece al intervalo [1, contarElementos() + 1]
     * Post: agrega el elemento en la posición indicada
     */
    void altaPosicion(T elemento, unsigned int posicion);

    /*
     * Post: agrega todos los elementos de otraLista a partir de la posición contarElementos() + 1
     */
    void agregar(Lista<T> &otraLista);

    /*
     * Pre: posición pertenece al intervalo [1, contarElementos()]
     * Post: devuelve el elemento en la posición indicada
     */
    T obtener(unsigned int posicion);

    /*
     * Pre: posición pertenece al intervalo: [1, contarElementos()]
     * Post: cambia elemento de posición indicada por elemento pasado
     */
    void asignar(T elemento, unsigned int posicion);

    /*
     * Pre: posición pertenece al intervalo: [1, contarElementos()]
     * Post: remueve de la Lista el elemento en la posición indicada
     */
    void remover(unsigned int posicion);

    /*
     * Post: deja cursor de Lista preparado para hacer nuevo recorrido colocandolo en NULL
     */
    void iniciarCursor();

    /*
     * Pre: se ha iniciado un recorrido (invocando el método iniciarCursor())
     * y desde entonces no se han agregado o removido elementos de la Lista.
     *
     * Post: mueve cursor, lo posiciona en siguiente elemento del recorrido
     * El valor de retorno indica si el cursor quedó posicionado sobre un elemento
     * o no (en caso de que la Lista esté vacía o no existan más elementos por recorrer.)
     */
    bool avanzarCursor();

    /*
     * Pre: el cursor está posicionado sobre un elemento de la Lista
     * (fue invocado el método avanzarCursor() y devolvió true)
     *
     * Post: devuelve el elemento en la posición del cursor.
     */
    T obtenerCursor();

    /*
     * Post: devuelve en booleano si la lista esta vacia o no
     */
    bool estaVacia();

    /*
     * Post: devuelve un entero con la cantidad de elementos en la lista
     */
    unsigned int contarElementos();

    /*
     * Post: devuelve -1 si el elemento no esta en la lista, si no devuelve el indice de su primer aparicion
     */
    int elementoPertenece( T elemento );


    /*
    * Post: Devuelve el ultimo elemento de la lista si esta no es nula
    */

    T bajaAlFinal();


private:
    /*
     * Pre: posicion pertenece al intervalo [1, contarElementos()]
     * Post: devuelve el nodo en la posicion indicada
     */
    Nodo<T> * obtenerNodo(unsigned int posicion);
};


template<class T> Lista<T>::Lista() {
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

template<class T> Lista<T>::Lista(Lista<T>&otraLista){
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;

    this->agregar(otraLista); //copia los elementos de otraLista
}

template<class T> Lista<T>::~Lista(){

    // mientras exista el primer nodo, se reasigna el puntero primero y se elimina el que era antes primer nodo
    while (this->primero != NULL){
        Nodo<T>* aBorrar = this->primero;
        this->primero = this->primero->obtenerSiguiente();
        delete aBorrar;
    }
}

template<class T> bool Lista<T>::estaVacia(){
    return (this->tamanio == 0);
}

template<class T> unsigned int Lista<T>::contarElementos() {
    return this->tamanio;
}

template<class T> void Lista<T>::altaFinal(T elemento) {
    this->altaPosicion(elemento, this->tamanio + 1);    //tamanio + 1 = nueva ultima posicion
}

template<class T>void Lista<T>::altaPosicion(T elemento, unsigned int posicion){

    if ((posicion> 0) && (posicion<= this->tamanio + 1)){   //valida la posicion de insercion
        Nodo<T> * nuevo = new Nodo<T>(elemento);

        /* si la posicion donde se desea insertar es la primera
         * se desplaza el primer nodo a la segunda posicion y
         * se inserta el nuevo en la primera
         */
        if (posicion == 1){
            nuevo->setSiguiente(this->primero);
            this->primero = nuevo;

        }

        /* si no, se apunta con anterior al nodo de la posición anterior,
         * el siguiente del nodo nuevo será el siguiente del anterior,
         * y el siguiente del anterior será el nuevo
         */
        else{
            Nodo<T> * anterior = this->obtenerNodo(posicion - 1);
            nuevo->setSiguiente(anterior->getSiguiente());
            anterior->setSiguiente(nuevo);
        }

        this->tamanio++;
        this->iniciarCursor();
    }
}

template<class T> void Lista<T>::agregar(Lista<T>& otraLista){
    otraLista.iniciarCursor();  //se inicializa el cursor de otraLista en NULL
    while (otraLista.avanzarCursor()){  //mientras exista un nodo apuntado por el cursor
        this->altaFinal(otraLista.obtenerCursor());   //se agrega al final el dato del nodo apuntado
    }
}

template<class T> T Lista<T>::obtener(unsigned int posicion){
    // se declara una variable que si no se le asigna un valor devuelve basura
    // mejorar la implementacion
    T elemento;
    // no es zero-indexado, y se vuelve incompatible para usarla
    if ((posicion > 0) && (posicion <= this->tamanio)){ //si la posicion recibida es valida
        elemento = this->obtenerNodo(posicion)->getDato();  //obtenerNodo(posicion) retorna un puntero al nodo del cual obtenemos el dato
    }
    return elemento;
}

template<class T> void Lista<T>::asignar(T elemento, unsigned int posicion){
    if ((posicion > 0) && (posicion <= this->tamanio)){
        this->obtenerNodo(posicion)->setDato(elemento);
    }
}

template<class T> void Lista<T>::remover(unsigned int posicion){

    if ((posicion> 0) && (posicion<= this->tamanio)){
        Nodo<T> * removido;

        if (posicion == 1){
            removido = this->primero;
            this->primero = removido->getSiguiente();

        } else{
            Nodo<T> * anterior = this->obtenerNodo(posicion - 1);
            removido = anterior->getSiguiente();
            anterior->setSiguiente(removido->getSiguiente());
        }

        delete removido;
        this->tamanio--;
        this->iniciarCursor();
    }
}

template<class T> void Lista<T>::iniciarCursor(){
    this->cursor = NULL;
}

template<class T> bool Lista<T>::avanzarCursor(){

    if (this->cursor == NULL){
        this->cursor = this->primero;

    } else{
        this->cursor = this->cursor->getSiguiente();
    }

    return (this->cursor != NULL);
}

template<class T> T Lista<T>::obtenerCursor(){
    T elemento;
    if (this->cursor != NULL){
        elemento = this->cursor->getDato();
    }
    return elemento;
}

template<class T> Nodo<T>* Lista<T>::obtenerNodo(unsigned int posicion){

    Nodo<T> * actual = this->primero;

    //se avanza hasta localizar el dato de la posición pasada por argumento y se retorna
    for (unsigned int i = 1; i < posicion; i++){
        actual = actual->getSiguiente();
    }

    return actual;
}

template<class T> T lista<T>::bajaAlFinal(){
    if(this->estaVacia()){
        throw "Lista sin elementos";
    }
    T elemento = this->obtener(this->tamanio);
    delete this->obtener(tam);
    this->tamanio--;
    this->altaFinal(this->obtener(tam));
    return elemento;
}

#endif //TATETI_2_0_LISTA_H
