/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include "soms.h"

int main(int argc, char** argv){
	/* Funcion principal del programa para crear, entrenar y aplicar mapas autoorganizados. */

	Nodo* nodo;
	nodo = crear_nodo(1,2,2);
	imprime_nodo(nodo,2);

	return 0;
}
