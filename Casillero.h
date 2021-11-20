#ifndef _CASILLERO_H_INCLUDED_
#define _CASILLERO_H_INCLUDED_
#include "Ficha.h"

const char VACIO = 'Z';

enum EstadoCasillero {
    BLOQUEADO,
    DESBLOQUEADO
};

class Casillero{
private:
    Ficha * ficha;
    Casillero **** casillerosAdyacentes;
    EstadoCasillero estado;

public:
    /*
     * Post: crea un Casillero con la Ficha vacia e inicializa
     * sus 27 casillerosAdyacentes
     */
    Casillero();

    /*
     * Post: crea un Casillero con la Ficha indicadas
     */
    Casillero(Ficha * ficha);

    /*
     * Post: libera toda la memoria solicitada para el Casillero
     */
    ~Casillero();

    /*
     * Pre: recibe las coordenadas respecto del mismo casillero tomando como referencia
     * que el origen es la posicion del casillero.
     * Post: asigna el casillero recibido como adyacente en la posicion recibida respecto
     * del mismo casillero. Lanza una excepcion si las coordenadas son inválidas
     */
    void asignarCasilleroAdyacente(int x, int y, int z, Casillero * casilleroAdyacente);

    /*
     * Pre: recibe las coordenadas respecto del mismo Casillero que se desea checkear
     * Post: devuelve true si el Casillero tiene un Casilllero adyacente existente
     * ubicado en las coordenadas recibidas y false en caso de que no
     */
    bool tieneAdyacente(unsigned int x, unsigned int y, unsigned int z);

    /*
     * Post: devuelve la Ficha del Casillero
     */
    Ficha * getFicha();

    /*
     * Post: establece la Ficha indicada en el Casillero
     */
    void setFicha(Ficha * nuevaFicha);

    /*
     * Pre:
     * Post:
     */
    Casillero * getAdyacente(unsigned int i, unsigned int  j, unsigned int  k);

    /*
     * Pre:
     * Post: devuelve un entero positivo que indica la cantidad de fichas iguales
     * respecto de la posicion recibida
     */
    unsigned int getLongitudFichasIguales(unsigned int i, unsigned int j, unsigned int k);

    bool estaBloqueado();

    void bloquear();

    void desbloquear();
};

#endif
