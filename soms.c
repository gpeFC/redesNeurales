/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soms.h"

int main(int argc, char** argv){
	int i,j,k;
	Mapa* mapa;
	iniciar_mapa(&mapa,2,2,2);
	printf("Mapa-dim: %d\n", mapa->dimension);
	printf("Mapa-X: %d\n", mapa->longitud_x);
	printf("Mapa-Y: %d\n", mapa->longitud_y);
	printf("Mapa-Alpha: %f\n", mapa->alpha);
	printf("Mapa-Sigma: %f\n", mapa->sigma);
	for(i=0;i<mapa->longitud_y;i++){
		for(j=0;j<mapa->longitud_x;j++){
			printf("Nodo-gano: %c\n", (((mapa->nodos)+i)+j)->gano);
		}
	}
	
	destruir_mapa(&mapa,2,2);

	return 0;
}
