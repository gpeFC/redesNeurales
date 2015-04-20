/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include "soms.h"

int main(int argc, char** argv){
	/* Funcion principal del programa para crear, entrenar y aplicar mapas autoorganizados. */
	int dim,x,y;
	dim = 3;
	x = 2;
	y = 2;
	Mapa* mapa;
	mapa = crear_mapa(dim,x,y);
	imprime_mapa(mapa);
	borrar_mapa(mapa,x,y);

	return 0;
}
