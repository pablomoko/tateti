#include "Juego.h"


int main () {


	try {
		Juego * tateti = new Juego();

		tateti->jugar();

		delete tateti;
	}
	catch (...) {
		return 1;
	}


    return 0;
}
