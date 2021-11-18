#ifndef __CARTA_H__
#define __CARTA_H__

#include <string>

typedef enum{
    SALTEAR, BLOQUEAR, ANULAR, REGRESAR, REPETIR, ROBAR
}funcion_t;
    
string *funcionalidades[] = {
    [SALTEAR] = "Saltea al jugador siguiente",
    [BLOQUEAR] = "Bloquea al jugador siguiente",
    [ANULAR] = "Anula un casillero del tablero",
    [REGRESAR] = "Vuelve atras una jugada",
    [REPETIR] = "Repetis tu turno",
    [ROBAR] = "Robas una carta a tu compañero",
};
    

class Carta {

private:
    unsigned int numero;
    funcion_t funcionalidad;


public:
    
    Carta( unsigned int numeroDeCarta, std::string descripcion );
    unsigned int getNumero();
    std::string getDescripcion(funcion_t);

};


Carta::Carta( unsigned int numeroDeCarta, std::string descripcion ){
    this->numero = numeroDeCarta;
    this->descripcion = descripcion;
}


unsigned int Carta::getNumero() {

    return this->numero;
}


std::string Carta::getDescripcion(funcinalidad_t funcionalidad) {

    return funcionalidades[funcionalidad];
}


#endif //__CARTA_H__
