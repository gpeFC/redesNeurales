/******************************************************************************
Mapas AutoOrganizados (SOMs) - Libreria
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct nodo{
	char gano;		// Indica si fue nodo ganador de la epoca actual de entrenamiento.
	int ganador;	// Numero de veces que fue nodo ganador durante el entrenamiento.
	int coord_x;	// Coordenada x del nodo.
	int coord_y;	// Coordenada y del nodo.	
	double* pesos;	// Pesos sinapticos del nodo.
}Nodo;

typedef struct mapa{
	int dimension;	// Tamanio/longitud del vector sinaptico de cada neurona.
	int longitud_x;	// Longitud en el eje X para el tamanio del mapa.
	int longitud_y;	// Longitud en el eje Y para el tamanio del mapa.
	double alpha;	// Ritmo/Factor de aprendizaje.
	double sigma;	// Radio de vecindad.
	Nodo** nodos;	// Matriz de nodos (Mapa).
}Mapa;

double pseudoaleatorio(int min, int max){
	return (((double)(rand()%(max-min)+min))/((double)max));
}

void mostrar_datos_nodo(Nodo** nodos, int dimnsn, int dim_x, int dim_y){
	int i,j,k;
	Nodo* nodo;
	for(i=0;i<dim_y;i++){
		for(j=0;j<dim_x;j++){
			nodo = *((nodos+i)+j);
			printf("Mapa-Nodo(%d,%d)\n", j, i);
			printf("\tGano: %c", nodo->gano);
			printf("\t\tGanador: %d\n", nodo->ganador);
			printf("\tCoord_X: %d", nodo->coord_x);
			printf("\tCoord_Y: %d\n", nodo->coord_y);
			printf("\tPesos(%d)\n", dimnsn);
			for(k=0;k<dimnsn;k++){
				printf("\t\tPesos[%d]: %f\n", (k+1), nodo->pesos[k]);
			}
		}
	}
}

void mostrar_datos_mapa(Mapa* mapa){
	printf("Mapa-dim: %d\n", mapa->dimension);
	printf("Mapa-X: %d\n", mapa->longitud_x);
	printf("Mapa-Y: %d\n", mapa->longitud_y);
	printf("Mapa-Alpha: %f\n", mapa->alpha);
	printf("Mapa-Sigma: %f\n", mapa->sigma);
	mostrar_datos_nodo((mapa->nodos), mapa->dimension, mapa->longitud_x, mapa->longitud_y);
}

void iniciar_pesos(double* pesos, int dimnsn){
	printf("\nEntro-iniciar-peso\n");
	pesos = (double*)malloc(sizeof(double)*dimnsn);
	if(!pesos)
		printf("\nNo se pudo reservar memoria...\n");
	else{
		int i;
		for(i=0;i<dimnsn;i++)
			*(pesos+i) = pseudoaleatorio(0,1000000);
		printf("\nInicio-pesos\n");
	}
}

void iniciar_nodo(Nodo* nodo, int x, int y, int dimnsn){
	nodo->gano = 'n';
	nodo->ganador = 0;
	nodo->coord_x = x;
	nodo->coord_y = y;
	printf("\nLleno-nodos-nodo-primeros\n");
	iniciar_pesos((nodo->pesos),dimnsn);
}

void iniciar_nodos(Nodo* nodos, int dim_x, int y, int dimnsn){
	nodos = (Nodo*)malloc(sizeof(Nodo)*dim_x);
	printf("\nReservo-nodos\n");
	if(!nodos)
		printf("\nNo se pudo reservar memoria...\n");
	else{
		int i;
		for(i=0;i<dim_x;i++)
			iniciar_nodo((nodos+i),i,y,dimnsn);
		printf("\nInicio-nodos-nodo\n");
	}
}

void iniciar_mapa(Mapa* mapa, int dimnsn, int dim_x, int dim_y){
	srand(time(NULL));
	mapa = (Mapa*)malloc(sizeof(Mapa));
	printf("\nReservo para mapa\n");
	if(!mapa)
		printf("\nNo se pudo reservar memoria...\n");
	else{
		Nodo** nodos;
		mapa->dimension = dimnsn;
		mapa->longitud_x = dim_x;
		mapa->longitud_y = dim_y;
		mapa->alpha = 0.0;
		mapa->sigma = 0.0;
		printf("\nLleno primeros-miembrs-mapa\n");
		nodos = (Nodo**)malloc(sizeof(Nodo*)*dim_y);
		printf("\nReservo-mapa-nodos\n");
		if(!nodos){
			printf("\nNo se pudo reservar memoria...\n");
		}
		else{
			int i;
			for(i=0;i<dim_y;i++)
				iniciar_nodos((*nodos+i), dim_x, i, dimnsn);
			printf("\nInicio-nodos\n");
			mapa->nodos = nodos;
		}
	}
}

void liberar_pesos(double* pesos){
	printf("\nEntro-liberar-pesos\n");
	if(pesos)
		free(pesos);
}

void liberar_nodos(Nodo* nodos, int dim_x){
	printf("\nEntro-liberar-nodos\n");
	if(nodos){
		printf("\nEntro-nodos\n");
		int i;
		double* pesos;
		for(i=0;i<dim_x;i++){
			printf("\nEntro-ciclo-lib-pesos\n");
			pesos = (nodos+i)->pesos;
			printf("Tam-pesos: %d\n", sizeof((nodos+i)->pesos));
			printf("\nAsigno-pesos\n");
			//liberar_pesos(pesos);
		}
		printf("\nLibero-pesos\n");
		free(nodos);
		printf("\nLibero-nodos-nodos\n");
	}
}

void liberar_mapa(Mapa* mapa, int dim_x, int dim_y){
	printf("\nEntro-liberar-mapa\n");
	if(mapa){
		int i;
		Nodo** nodos;
		nodos = mapa->nodos;
		for(i=0;i<dim_y;i++)
			liberar_nodos((*(nodos+i)), dim_x);
		printf("\nLibero-nodos\n");
		free(mapa);
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
	srand(time(NULL));
}

