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

void imprime_pesos(double* pesos, int dimnsn){
	/* codigo */
	if(pesos){
		/* sentencias */
		int i;
		for(i=0;i<dimnsn;i++){
			/* sentencias */
			printf("Peso(%d): %f\n", i, pesos[i]);
		}
	}
}

void imprime_nodo(Nodo* nodo, int dimnsn){
	/* codigo */
	if(nodo){
		/* sentencias */
		printf("Gano: %c\n", nodo->gano);
		printf("Ganador: %d\n", nodo->ganador);
		printf("Coords: (%d,%d)\n", nodo->coord_x, nodo->coord_y);
		imprime_pesos(nodo->pesos, dimnsn);
	}
}

void imprime_mapa(Mapa* mapa, int dim_y, int dim_x, int dimnsn){
	/* codigo */
	if(mapa){
		/* sentencias */
		int i,j;
		printf("\tMapa AutoOrganizado.\n");
		printf("Dimension: %d\n", mapa->dimension);
		printf("Longitud: (%d,%d)\n", mapa->longitud_x,mapa->longitud_y);
		printf("RdA: %f\n", mapa->alpha);
		printf("RdV: %f\n", mapa->sigma);
		printf("Nodos:\n");
	}
}

double* crear_pesos(int dimnsn){
	/* codigo */
	double* pesos;
	pesos = NULL;
	pesos = (double*)malloc(sizeof(double)*dimnsn);
	if(!pesos){
		/* sentencias */
		printf("No se pudo reservar memoria.\n");
	}
	else{
		/* sentencias */
		int i;
		for(i=0;i<dimnsn;i++){
			/* sentencias */
			pesos[i] = pseudoaleatorio(0,1000000);
		}
	}
	return pesos;
}

Nodo* crear_nodo(int x, int y, int dimnsn){
	/* codigo */
	Nodo* nodo;
	nodo = NULL;
	nodo = (Nodo*)malloc(sizeof(Nodo));
	if(!nodo){
		/* sentencias */
		printf("No se pudo reservar memoria.\n");
	}
	else{
		/* sentencias */
		nodo->gano = 'n';
		nodo->ganador = 0;
		nodo->coord_x = x;
		nodo->coord_y = y;
		nodo->pesos = crear_pesos(dimnsn);
	}
	return nodo;
}

Nodo* crear_nodos(int dim_x, int y, int dimnsn){
	/* codigo */
	Nodo* nodos;
	nodos = NULL;
	nodos = (Nodo*)malloc(sizeof(Nodo)*dim_x);
	if(!nodos){
		/* sentencias */
		printf("No se pudo reservar memoria.\n");
	}
	else{
		/* sentencias */
		int i;
		for(i=0;i<dim_x;i++){
			/* sentencias */
			nodos[i].gano = 'n';
			nodos[i].ganador = 0;
			nodos[i].coord_x = i;
			nodos[i].coord_y = y;
			nodos[i].pesos = crear_pesos(dimnsn);
		}
	}
	return nodos;
}

Mapa* crear_mapa(int dimnsn, int dim_x, int dim_y){
	/* codigo */
	Mapa* mapa;
	mapa = NULL;
	mapa = (Mapa*)malloc(sizeof(Mapa));
	if(!mapa){
		/* sentencias */
		printf("No se pudo reservar memoria.\n");
	}
	else{
		/* sentencias */
		mapa->dimension = dimnsn;
		mapa->longitud_x = dim_x;
		mapa->longitud_y = dim_y;
		mapa->alpha = 0.0;
		mapa->sigma = 0.0;
		mapa->nodos = NULL;
		mapa->nodos = (Nodo**)malloc(sizeof(Nodo*)*dim_y);
		if(!(mapa->nodos)){
			/* sentencias */
			printf("No se pudo reservar memoria.\n");
		}
		else{
			/* sentencias */
			int i,j;
			for(i=0;i<dim_y;i++){
				/* sentencias */
				mapa->nodos[i] = NULL;
				mapa->nodos[i] = crear_nodos(dim_x,i,dimnsn);
			}
		}
	}
	return mapa;
}

void borrar_pesos(double* pesos){
	/* codigo */
	if(pesos){
		/* sentencias */
		free(pesos);
		printf("\nlibera-pesos\n");
		pesos = NULL;
	}
}

void borrar_nodos(Nodo* nodos, int dim_x){
	/* codigo */
	if(nodos){
		/* sentencias */
		int i;
		for(i=0;i<dim_x;i++){
			/* sentencias */
			borrar_pesos((nodos+i)->pesos);
		}
		free(nodos);
		printf("\nlibera-nodos\n");
		nodos = NULL;
	}
}

void borrar_mapa(Mapa* mapa, int dim_x, int dim_y){
	/* codigo */
	if(mapa){
		/* sentencias */
		int i;
		for(i=0;i<dim_y;i++){
			/* sentencias */
			borrar_nodos(mapa->nodos[i],dim_x);
		}
		free(mapa);
		printf("\nlibera-mapa\n");
		mapa = NULL;
	}
}