#ifndef _FICHA_H_INCLUDED_
#define _FICHA_H_INCLUDED_

class Ficha{

private:
    char simbolo;


public:

    /**
     * pre:
     * post:
     * */
    Ficha(char simbolo);

    /**
     * pre:
     * post:
     * */
    ~Ficha();

    /**
     * pre:-
     * post: Devuelve valor del simbolo(char).
     **/
    char getSimbolo();

    /**
     * pre:
     * post:
     **/
    bool esIgual(Ficha * ficha1,Ficha * ficha2){

        try{
            return (ficha1->getSimbolo() == ficha2->getSimbolo()); 
        }
        catch(...){
        }
        
        return false;
    }

private:

    /**
     * pre:-
     * post:valida que el simbolo ingresado no sea '\0  o ' ' o lanza un excepcion en caso contrario.
     **/
    void validar(char simbolo); 
    
};








#endif