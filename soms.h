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
	/* Funcion para mostrar en pantalla los datos contenidos en una estructura <Mapa>. */
	printf("Mapa-dim: %d\n", mapa->dimension);
	printf("Mapa-X: %d\n", mapa->longitud_x);
	printf("Mapa-Y: %d\n", mapa->longitud_y);
	printf("Mapa-Alpha: %f\n", mapa->alpha);
	printf("Mapa-Sigma: %f\n", mapa->sigma);
	//mostrar_datos_nodo((mapa->nodos), mapa->longitud_x, mapa->longitud_y, mapa->dimension);
}

void iniciar_pesos(double* pesos, int dimnsn){
	/* Funcion para crear e inicializar un vector <pesos>. */
	double* nuevos_pesos;
	nuevos_pesos = NULL;
	nuevos_pesos = (double*)malloc(sizeof(double)*dimnsn);
	if(!nuevos_pesos){
		/* No se pudo reservar memoria para un vector <pesos>. */
		printf("No se pudo reservar memoria para el vector <pesos>.\n");
	}
	else{
		/* Se reservo memoria suficiente para un vector <pesos>. */
		int i;
		for(i=0;i<dimnsn;i++){
			/* Bucle para llenar el vector <pesos> con valores pseudoaleatorios. */
			*(nuevos_pesos+i) = pseudoaleatorio(0,1000000);
		}
		pesos = nuevos_pesos;
	}
}

void iniciar_nodo(Nodo* nodo, int x, int y, int dimnsn){
	/* Funcion para crear inicializar una estructura <Nodo>. */
	Nodo* nuevo_nodo;
	nuevo_nodo = NULL;
	nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
	if(!nuevo_nodo){
		/* No se pudo reservar memoria para una estructura <Nodo>. */
		printf("No se pudo reservar memoria para una estructura <Nodo>.\n");
	}
	else{
		/* Se reservo memoria suficiente para una estructura <Nodo>. */
		nuevo_nodo->gano = 'n';
		nuevo_nodo->ganador = 0;
		nuevo_nodo->coord_x = x;
		nuevo_nodo->coord_y = y;
		iniciar_pesos((nuevo_nodo->pesos),dimnsn);
		nodo = nuevo_nodo;
	}
}

void iniciar_nodos(Nodo* nodos, int dim_x, int y, int dimnsn){
	/* Funcion para crear e inicializar un vector de estructuras <Nodo>. */
	Nodo* nuevos_nodos;
	nuevos_nodos = NULL;
	nuevos_nodos = (Nodo*)malloc(sizeof(Nodo)*dim_x);
	if(!nuevos_nodos){
		/* No se pudo reservar memoria para un vector de estructuras <Nodo>. */
		printf("No se pudo reservar memoria para un vector de estructuras <Nodo>.\n");
	}
	else{
		/* Se reservo memoria suficiente para un vector de estructuras <Nodo>. */
		int i;
		for(i=0;i<dim_x;i++){
			/* Bucle para crear e inicializar cada elemento del vector de estructuras <Nodo>. */
			iniciar_nodo((nuevos_nodos+i),i,y,dimnsn);
		}
		nodos = nuevos_nodos;
	}
}

void iniciar_mapa(Mapa* mapa, int long_x, int long_y, int dimnsn){
	/* Funcion para crear e inicializar una estructura <Mapa>. */
	srand(time(NULL));
	Mapa* nuevo_mapa;
	nuevo_mapa = NULL;
	nuevo_mapa = (Mapa*)malloc(sizeof(Mapa));
	if(!nuevo_mapa){
		/* No se pudo reservar memoria para una estructura <Mapa>. */
		printf("No se pudo reservar memoria para una estructura <Mapa>.\n");
	}
	else{
		/* Se reservo memoria suficiente para una estructura <Mapa>. */
		Nodo** nodos;
		nodos = NULL;
		nuevo_mapa->dimension = dimnsn;
		nuevo_mapa->longitud_x = long_x;
		nuevo_mapa->longitud_y = long_y;
		nuevo_mapa->alpha = 0.0;
		nuevo_mapa->sigma = 0.0;
		nodos = (Nodo**)malloc(sizeof(Nodo*)*long_y);
		if(!nodos){
			/* No se pudo reservar memoria para un vector de punteros a vectores de estructuras <Nodo>. */
			printf("No se pudo reservar memoria para un vector de punteros a vectores de estructuras <Nodo>.\n");
		}
		else{
			/* Se reservo memoria suficiente para un vector de punteros a vectores de estructuras <Nodo>. */
			int i;
			for(i=0;i<long_y;i++){
				/* Bucle para crear e inicializar cada elemento del vector de punteros a vectores de estructuras <Nodo>. */
				iniciar_nodos(*(nodos+i),long_x,i,dimnsn);
			}
			nuevo_mapa->nodos = nodos;
		}
		mapa = nuevo_mapa;
	}
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
			printf("\nAsigno-nodo\n");
			pesos = nodo->pesos;
			printf("\nAsigno-pesos\n");
			liberar_pesos(pesos);
		}
		free(nodos);
	}
}

void liberar_mapa(Mapa* mapa, int long_x, int long_y){
	/* Funcion para liberar la memoria reservada para una estructura <Mapa>. */
	if(mapa){
		/* La estructura <Mapa> contiene memoria reservada para ser liberada. */
		int i;
		Nodo** nodos;
		nodos = mapa->nodos;
		for(i=0;i<long_y;i++){
			/* Bucle para liberar cada elemento del vector de punteros a vectores de estructuras <Nodo>. */
			liberar_nodos(*(nodos+i),long_x);
		}
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
}

