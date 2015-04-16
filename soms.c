/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include "soms.h"

int main(int argc, char** argv){
	/* Funcion principal del programa para crear, entrenar y aplicar mapas autoorganizados. */

	Mapa* mapa;
	mapa = NULL;

	mapa = crear_mapa(2,1,1);

	imprime_mapa(mapa,1,1,2);

	borrar_mapa(mapa,1,1);

	if(mapa==NULL){
		/* sentencias */
		printf("Se anulo mapa.\n");
	}

	printf("\n\n");

	imprime_mapa(mapa,1,1,2);

	if(mapa==NULL){
		/* sentencias */
		printf("Se anulo mapa.\n");
	}

	borrar_mapa(mapa,1,1);

	return 0;
}
