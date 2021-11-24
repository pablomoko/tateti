#ifndef __CONSTANTES_H__
#define __CONSTANTES_H__


#include <string>


#define VACIO '.' // tira error si hay espacio ' '


enum EstadoFicha {
    FICHA_DESBLOQUEADA, 
    FICHA_BLOQUEADA
};


enum EstadoCasillero {
    CASILLERO_BLOQUEADO,
    CASILLERO_DESBLOQUEADO
};

/*
enum EstadoJugador {
    JUGADOR_BLOQUEADO,
    JUGANDO,
    DOBLE_TURNO
};
*/


// PARA CARTAS
typedef enum{
    SALTEAR, BLOCK_FICHA, BLOCK_CASILLERO, REGRESAR, REPETIR, BLOCK_CASILLERO
}funcion_t;
    
string *funcionalidades[] = {
    [SALTEAR] = "Saltea al jugador siguiente",
    [BLOCK_FICHA] = "Bloquea al jugador siguiente",
    [BLOCK_CASILLERO] = "Anula un casillero del tablero",
    [REGRESAR] = "Vuelve atras una jugada",
    [REPETIR] = "Repetis tu turno",
    [ROBAR_CARTA] = "Robas una carta a tu compañero",
};

#endif  /* __CONSTANTES_H__ */