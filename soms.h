/******************************************************************************
Mapas AutoOrganizados (SOMs) - Libreria
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct nodo{
	/* Estructura para almacenar datos de un nodo de un mapa autoorganizado. */
	char gano;		// Indica si fue nodo ganador de la epoca actual de entrenamiento.
	int ganador;	// Numero de veces que fue nodo ganador durante el entrenamiento.
	int coord_x;	// Coordenada x del nodo.
	int coord_y;	// Coordenada y del nodo.	
	double* pesos;	// Pesos sinapticos del nodo.
}Nodo;

typedef struct mapa{
	/* Estructura para almacenar datos de un mapa autoorganizado. */
	int dimension;	// Tamanio/longitud del vector sinaptico de cada neurona.
	int longitud_x;	// Longitud en el eje X para el tamanio del mapa.
	int longitud_y;	// Longitud en el eje Y para el tamanio del mapa.
	double alpha;	// Ritmo/Factor de aprendizaje.
	double sigma;	// Radio de vecindad.
	Nodo** nodos;	// Matriz de nodos (Mapa).
}Mapa;

double pseudoaleatorio(int min, int max){
	/* Funcion para generar y devolver un numero real pseudoaleatorio de un rango determinado. */
	return (((double)(rand()%(max-min)+min))/((double)max));
}

void mostrar_datos_nodo(Nodo** nodos, int dim_x, int dim_y, int dimnsn){
	/* Funcion para mostrar en pantalla los datos contenidos en un vector de estructuras <Nodo>. */
	int i,j,k;
	Nodo* nodo;
	double* pesos;
	for(i=0;i<dim_y;i++){
		for(j=0;j<dim_x;j++){
			nodo = (*(nodos+i)+j);
			printf("Mapa-Nodo(%d,%d)\n", j, i);
			printf("\tGano: %c", nodo->gano);
			printf("\t\tGanador: %d\n", nodo->ganador);
			printf("\tCoord_X: %d", nodo->coord_x);
			printf("\tCoord_Y: %d\n", nodo->coord_y);
			printf("\tPesos(%d)\n", dimnsn);
			for(k=0;k<dimnsn;k++){
				pesos = nodo->pesos;
				printf("\t\tPesos[%d]: %f\n", (k+1), *(pesos+k));
			}
		}
	}
}

void mostrar_datos_mapa(Mapa* mapa){
	/* Funcion para mostrar en pantalla los datos contenidos en una estructura <Mapa>. */
	printf("Mapa-dim: %d\n", mapa->dimension);
	printf("Mapa-X: %d\n", mapa->longitud_x);
	printf("Mapa-Y: %d\n", mapa->longitud_y);
	printf("Mapa-Alpha: %f\n", mapa->alpha);
	printf("Mapa-Sigma: %f\n", mapa->sigma);
	mostrar_datos_nodo((mapa->nodos), mapa->longitud_x, mapa->longitud_y, mapa->dimension);
}

double* iniciar_pesos(int dimnsn){
	/* codigo */
	double* pesos;
	pesos = NULL;
	pesos = (double*)malloc(sizeof(double));
	if(!pesos){
		/* sentencias */
		printf("No se pudo reservar memoria para el vector <pesos>.\n");
	}
	else{
		/* sentencias */
		int i;
		for(i=0;i<dimnsn;i++){
			/* sentencias */
			*(pesos+i) = pseudoaleatorio(0,1000000);
		}
	}
	return pesos;
}

Nodo* iniciar_nodo(int x, int y, int dimnsn){
	/* Funcion para crear inicializar una estructura <Nodo>. */
	Nodo* nodo;
	nodo = NULL;
	nodo = (Nodo*)malloc(sizeof(Nodo));
	if(!nodo){
		/* No se pudo reservar memoria para una estructura <Nodo>. */
		printf("No se pudo reservar memoria para una estructura <Nodo>.\n");
	}
	else{
		/* Se reservo memoria suficiente para una estructura <Nodo>. */
		nodo->gano = 'n';
		nodo->ganador = 0;
		nodo->coord_x = x;
		nodo->coord_y = y;
		nodo->pesos = iniciar_pesos(dimnsn);
	}
	return nodo;
}

Nodo* iniciar_nodos(int dim_x, int y, int dimnsn){
	/* Funcion para crear e inicializar un vector de estructuras <Nodo>. */
	Nodo* nodos;
	nodos = NULL;
	nodos = (Nodo**)malloc(sizeof(Nodo*)*dim_x);
	if(!nodos){
		/* No se pudo reservar memoria para un vector de estructuras <Nodo>. */
		printf("No se pudo reservar memoria para un vector de estructuras <Nodo>.\n");
	}
	else{
		/* Se reservo memoria suficiente para un vector de estructuras <Nodo>. */
		int i;
		for(i=0;i<dim_x;i++){
			/* Bucle para crear e inicializar cada elemento del vector de estructuras <Nodo>. */
			*(nodos+i) = iniciar_nodo(i,y,dimnsn);
		}
	}
	return nodos;
}

Mapa* iniciar_mapa(int long_x, int long_y, int dimnsn){
	/* Funcion para crear e inicializar una estructura <Mapa>. */
	srand(time(NULL));
	Mapa* mapa;
	mapa = NULL;
	mapa = (Mapa*)malloc(sizeof(Mapa));
	if(!mapa){
		/* No se pudo reservar memoria para una estructura <Mapa>. */
		printf("No se pudo reservar memoria para una estructura <Mapa>.\n");
	}
	else{
		/* Se reservo memoria suficiente para una estructura <Mapa>. */
		mapa->dimension = dimnsn;
		mapa->longitud_x = long_x;
		mapa->longitud_y = long_y;
		mapa->alpha = 0.0;
		mapa->sigma = 0.0;
		mapa->nodos = (Nodo**)malloc(sizeof(Nodo*)*long_y);
		if(!(mapa->nodos)){
			/* No se pudo reservar memoria para un vector de punteros a vectores de estructuras <Nodo>. */
			printf("No se pudo reservar memoria para un vector de punteros a vectores de estructuras <Nodo>.\n");
		}
		else{
			/* Se reservo memoria suficiente para un vector de punteros a vectores de estructuras <Nodo>. */
			int i;
			for(i=0;i<long_y;i++){
				/* Bucle para crear e inicializar cada elemento del vector de punteros a vectores de estructuras <Nodo>. */
				mapa->(nodos+i) = iniciar_nodos(long_x,i,dimnsn);
			}
		}
	}
	return mapa;
}

void liberar_pesos(double* pesos){
	/* Funcion para liberar la memoria reservada para un vector <pesos>. */
	if(pesos){
		/* El vector <pesos> contiene memoria reservada para ser liberada. */
		free(pesos);
	}
}

void liberar_nodos(Nodo* nodos, int long_x){
	/* Funcion para liberar la memoria reservada para un vector de estructuras <Nodo>. */
	if(nodos){
		/* El vector de estructuras <Nodo> contiene memoria reservada para ser liberada. */
		int i;
		double* pesos;
		Nodo* nodo;
		for(i=0;i<long_x;i++){
			/* Bucle para liberar cada vector <pesos> contenidos en cada estructura <Nodo> del vector. */
			nodo = (nodos+i);
			pesos = nodo->pesos;
			liberar_pesos(pesos);
		}
		free(nodos);
	}
}

void liberar_mapa(Mapa** mapa, int long_x, int long_y){
	/* Funcion para liberar la memoria reservada para una estructura <Mapa>. */
	if(mapa){
		/* La estructura <Mapa> contiene memoria reservada para ser liberada. */
		int i;
		Nodo** nodos;
		nodos = (*mapa)->nodos;
		for(i=0;i<long_y;i++){
			/* Bucle para liberar cada elemento del vector de punteros a vectores de estructuras <Nodo>. */
			liberar_nodos(*(nodos+i),long_x);
		}
		free(*mapa);
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

