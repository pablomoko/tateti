#include "Carta.h"


std::string funcionalidades[6] = {
    [SALTEAR] = "Saltea al jugador siguiente",
    [BLOCK_FICHA] = "Bloquea una ficha puesta en el tablero",
    [BLOCK_CASILLERO] = "Anula un casillero del tablero",
    [REGRESAR] = "Vuelve atras una jugada",
    [REPETIR] = "Repetis tu turno",
    [ROBAR_CARTA] = "Robas una carta a tu compañero",
};



Carta::Carta( funcion_t funcion ){

    this->funcion = funcion;
}


funcion_t Carta::getFuncionalidad() {

    return this->funcion;
}


std::string Carta::getDescripcion() {

    return funcionalidades[this->funcion];
}


