/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soms.h"

int main(int argc, char** argv){
	Mapa *mapa;
	construir_mapa(&mapa,2,2,2);
	//destruir_mapa(&mapa,2,2);
	/*
	char* var;
	Nodo* nodo;
	printf("Tamanio(*char): %d\n", sizeof(var));
	printf("Tamanio(nodo): %d\n", sizeof(*nodo));
	printf("Tamanio(nodo->char): %d\n", sizeof(nodo->gano));
	printf("Tamanio(nodo->int): %d\n", sizeof(nodo->coord_x));
	printf("Tamanio(nodo->int): %d\n", sizeof(nodo->coord_y));
	printf("Tamanio(nodo->int): %d\n", sizeof(nodo->ganador));
	printf("Tamanio(nodo->*double): %d\n", sizeof(nodo->pesos));
	iniciar_nodo(&nodo,2,3,2);

	printf("{(%d,%d)(%c)(%d)}\n", nodo->coord_x,nodo->coord_y,nodo->gano,nodo->ganador);
	printf("Peso1: %f\n", nodo->pesos[0]);
	printf("Peso2: %f\n", nodo->pesos[1]);
	
	printf("Tamanio(char): %d\n", sizeof(char));
	printf("Tamanio(int): %d\n", sizeof(int));
	printf("Tamanio(float): %d\n", sizeof(float));
	printf("Tamanio(double): %d\n", sizeof(double));
	printf("Tamanio(Nodo): %d\n", sizeof(Nodo));
	printf("Tamanio(Mapa): %d\n", sizeof(Mapa));

	destruir_nodo(&nodo);
	*/

	return 0;
}
