/******************************************************************************
Mapas AutoOrganizados (SOMs) - Libreria
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct nodo{
	char gano;			// Indica si fue nodo ganador de la epoca actual de entrenamiento.
	int coord_x;		// Coordenada x del nodo.
	int coord_y;		// Coordenada y del nodo.
	int ganador;		// Numero de veces que fue nodo ganador durante el entrenamiento.
	double* pesos;	// Pesos sinapticos del nodo.
}Nodo;

typedef struct mapa{
	int unsigned dimension;	// Tamanio/longitud del vector sinaptico de cada neurona.
	int unsigned longitud_x;	// Longitud en el eje X para el tamanio del mapa.
	int unsigned longitud_y;	// Longitud en el eje Y para el tamanio del mapa.
	double alpha;		// Ritmo/Factor de aprendizaje.
	double sigma;		// Radio de vecindad.
	Nodo** nodos;		// Matriz de nodos (Mapa).
}Mapa;

double pseudoaleatorio(double min, double max){
	return (drand48()*(max-min)+max);
}

Nodo* crear_nodo(){
	Nodo* nodo;
	nodo = NULL;
	nodo = (Nodo*)malloc(sizeof(Nodo));
	return nodo;
}

Mapa* crear_mapa(){
}

void iniciar_nodo(Nodo** nodo, int x, int y, int dimnsn){
	Nodo* nuevo;
	nuevo = crear_nodo();
	if(nuevo==NULL){
		printf("\nNo se pudo reservar memoria para la estructura <Nodo>.\n");
	}
	else{
		srand48(time(NULL));
		int indice;
		double* pesos;
		nuevo->gano = 'n';
		nuevo->coord_x = x;
		nuevo->coord_y = y;
		nuevo->ganador = 0;
		pesos = (double*)malloc(sizeof(double)*dimnsn);
		for(indice=0;indice<dimnsn;indice++)
			*(pesos+indice) = drand48();
		nuevo->pesos = pesos;
		*nodo = nuevo;
	}
}

void iniciar_mapa(){
}

void destruir_nodo(Nodo** nodo){
	if(nodo!=NULL)
		free((*nodo)->pesos);
		free(*nodo);
}

void destruir_mapa(){
}
