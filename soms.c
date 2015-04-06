/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soms.h"

int main(int argc, char** argv){
	Nodo* nodo;
	iniciar_nodo(&nodo,2,3,2);

	printf("{(%d,%d)(%c)(%d)}\n", nodo->coord_x,nodo->coord_y,nodo->gano,nodo->ganador);
	printf("Peso1: %f\n", nodo->pesos[0]);
	printf("Peso2: %f\n", nodo->pesos[1]);

	printf("Tamanio(int): %d\n", sizeof(int));
	printf("Tamanio(float): %d\n", sizeof(float));
	printf("Tamanio(double): %d\n", sizeof(double));
	printf("Tamanio(Nodo): %d\n", sizeof(Nodo));
	printf("Tamanio(Mapa): %d\n", sizeof(Mapa));

	destruir_nodo(&nodo);

	return 0;
}