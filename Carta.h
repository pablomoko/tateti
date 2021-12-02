#ifndef CARTA_H_
#define CARTA_H_


#include <string>
#include "Constantes.h"


// ----------------------------------------------------------------------------
// PARA CARTAS
typedef enum{
    SALTEAR, BLOCK_FICHA, BLOCK_CASILLERO, REGRESAR, REPETIR, ROBAR_CARTA,
}funcion_t;

extern std::string funcionalidades[6];
// ----------------------------------------------------------------------------




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




#endif /* CARTA_H_ */
