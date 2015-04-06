/******************************************************************************
Mapas AutoOrganizados (SOMs) - Libreria
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct nodo{
	char unsigned gano;			// Indica si fue nodo ganador de la epoca actual de entrenamiento.
	int unsigned coord_x;		// Coordenada x del nodo.
	int unsigned coord_y;		// Coordenada y del nodo.
	int unsigned ganador;		// Numero de veces que fue nodo ganador durante el entrenamiento.
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

double pseudoaleatorio(int min, int max){
	return (((double)(rand()%(max-min)+min))/((double)max));
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
		srand(time(NULL));
		int indice;
		double* pesos;
		nuevo->gano = 'n';
		nuevo->coord_x = x;
		nuevo->coord_y = y;
		nuevo->ganador = 0;
		pesos = (double*)malloc(sizeof(double)*dimnsn);
		for(indice=0;indice<dimnsn;indice++)
			*(pesos+indice) = pseudoaleatorio(0,1000000);
		nuevo->pesos = pesos;
		*nodo = nuevo;
	}
}

void construir_mapa(Mapa** mapa, int unsigned dimnsn, int unsigned dim_x, int unsigned dim_y){
	srand(time(NULL));
	int i,j,k;
	double* pesos;
	Nodo** nodos;
	Mapa nuevo;
	nuevo.dimension = dimnsn;
	nuevo.longitud_x = dim_x;
	nuevo.longitud_y = dim_y;
	nuevo.alpha = 0.0;
	nuevo.sigma = 0.0;
	nodos = (Nodo**)malloc(sizeof(Nodo*)*dim_y);
	for(i=0;i<dim_y;i++){
		*(nodos+i) = (Nodo*)malloc(sizeof(Nodo)*dim_x);
		for(j=0;j<dim_x;j++){
			iniciar_nodo(((nodos+i)+j),j,i,dimnsn);
		}
	}
	
	for(i=0;i<dim_y;i++){
		*(nodos+i) = (Nodo*)malloc(sizeof(Nodo)*dim_x);
		for(j=0;j<dim_x;j++){
			printf("Gano: %c\n", (*((nodos+i)+j))->gano);
			printf("(X,Y): (%d,%d)\n", (*(nodos+i)+j)->coord_x, (*(nodos+i)+j)->coord_y);
			printf("Ganador: %d\n", (*(nodos+i)+j)->ganador);
			//for(k=0;k<dimnsn;k++)
				//printf("Peso[%d,%d](%f)\n", j, i, (*(nodos+i)+j)->(*(pesos[k])));
		}
	}

	nuevo.nodos = nodos;
	*mapa = &nuevo;
}

void destruir_nodo(Nodo** nodo){
	if(nodo!=NULL){
		free((*nodo)->pesos);
		free(*nodo);
	}
}

void destruir_mapa(Mapa** mapa, int unsigned dim_x, int unsigned dim_y){
	if(mapa!=NULL){
		int i,j;
		Nodo** nodos;
		nodos = (*mapa)->nodos;
		for(i=0;i<dim_y;i++){
			for(j=0;j<dim_x;j++){
				free((*(nodos+i)+j)->pesos);
				free((*(nodos+i)+j));
			}
		}
	}
}

void ajustar_alpha(){
}

void ajustar_sigma(){
}

void ajustar_nodos(){
}

void calcular_distancia(){
}

void calcular_vecindad(){
}

void ejecutar_mapeo(){
}

void entrenar_mapeo(){
}

