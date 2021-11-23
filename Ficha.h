#ifndef _FICHA_H_INCLUDED_
#define _FICHA_H_INCLUDED_

#include "constantes.h"

class Ficha{

private:
    char simbolo;
    EstadoFicha estado;


public:

    /*
     * Post: crea una ficha con el simbolo indicado y estado desbloqueado
     * */
    Ficha(char simbolo);


    /*
     * Post: libera toda la memoria solicitada para la Ficha
     * */
    ~Ficha();


    /*
     * Post: devuelve el simbolo de la Ficha
     **/
    char getSimbolo();


    /*
     * Post: devuelve true si los simbolos de la Ficha recibida es igual al simbolo
     * y false si no lo son
     **/
    bool esIgual(Ficha * ficha2);


    /*
     * Post: atributo estado cambia a bloqueado
     */
    void bloquear();


    /*
     * Post: atributo estado cambia a desbloqueado
     */
    void desbloquear();


    /*
     *Post: devuelve true si atributo estado == bloqueado
     */
    bool estaBloqueada();


private:

    /*
     * Post:valida que el simbolo ingresado no sea '\0  o ' ' o lanza un excepcion en caso contrario.
     **/
    void validar(char simbolo);

};

#endif
