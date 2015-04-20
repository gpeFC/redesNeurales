/******************************************************************************
Mapas AutoOrganizados (SOMs) - Libreria
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct nodo{
	/* Estructura para almacenar datos de un nodo en un mapa autoorganizado. */
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

void imprime_pesos(double* pesos, int dimnsn){
	/* codigo */
	if(pesos){
		/* sentencias */
		int i;
		for(i=0;i<dimnsn;i++){
			/* sentencias */
			printf("(%f)", *(pesos+i));
		}
		printf("\n");
	}
}

void imprime_nodos(Nodo** nodos, int dimnsn, int dim_x, int dim_y){
	/* codigo */
	if(nodos){
		/* sentencias */
		int i,j;
		for(i=0;i<dim_y;i++){
			/* sentencias */
			for(j=0;j<dim_x;j++){
				/* sentencias */
				printf("Nodo[%d,%d]\n", i,j);
				printf(" Gano: %c\n", (*(nodos+i)+j)->gano);
				printf(" Ganador: %d\n", (*(nodos+i)+j)->ganador);
				printf(" Pesos[%d]: ", dimnsn);
				imprime_pesos((*(nodos+i)+j)->pesos,dimnsn);
			}
		}
	}
}

void imprime_mapa(Mapa* mapa){
	/* codigo */
	if(mapa){
		/* sentencias */
		printf("Mapa AutoOrganizado.\n");
		printf("Dimension: %d\n", mapa->dimension);
		printf("Tamanio: (%d,%d)\n", mapa->longitud_x,mapa->longitud_y);
		printf("Alpha: %f\n", mapa->alpha);
		printf("Sigma: %f\n", mapa->sigma);
		imprime_nodos(mapa->nodos,mapa->dimension,mapa->longitud_x,mapa->longitud_y);
	}
}

double pseudoaleatorio(int min, int max){
	/* Funcion para generar y devolver un numero real pseudoaleatorio de un rango determinado. */
	return (((double)(rand()%(max-min)+min))/((double)max));
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
		srand(time(NULL));
		for(i=0;i<dimnsn;i++){
			/* sentencias */
			*(pesos+i) = pseudoaleatorio(0,1000000);
		}
	}
	return pesos;
}

Nodo** crear_nodos(int dimnsn, int dim_x, int dim_y){
	/* codigo */
	Nodo** nodos;
	nodos = NULL;
	nodos = (Nodo**)malloc(sizeof(Nodo*)*dim_y);
	if(!nodos){
		/* sentencias */
		printf("No se pudo reservar memoria.\n");
	}
	else{
		/* sentencias */
		int i,j;
		for(i=0;i<dim_y;i++){
			/* sentencias */
			*(nodos+i) = (Nodo*)malloc(sizeof(Nodo)*dim_x);
			for(j=0;j<dim_x;j++){
				/* sentencias */
				(*(nodos+i)+j)->gano = 'n';
				(*(nodos+i)+j)->ganador = 0;
				(*(nodos+i)+j)->coord_x = j;
				(*(nodos+i)+j)->coord_y = i;
				(*(nodos+i)+j)->pesos = crear_pesos(dimnsn);
			}
		}
	}
	return nodos;
}

Mapa* crear_mapa(int dimnsn, int long_x, int long_y){
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
		mapa->longitud_x = long_x;
		mapa->longitud_y = long_y;
		mapa->alpha = 0.0;
		mapa->sigma = 0.0;
		mapa->nodos = crear_nodos(dimnsn,long_x,long_y);
	}
	return mapa;
}

void ajustar_alpha(int epocas, int actual, double* alpha, double alpha_ini, double alpha_fin){
	/* codigo */
	*alpha = alpha_ini * pow((alpha_fin/alpha_ini),(actual/epocas));
}

void ajustar_sigma(int epocas, int actual, double* sigma, double sigma_ini, double sigma_fin){
	/* codigo */
	*sigma = sigma_ini * pow((sigma_fin/sigma_ini),(actual/epocas));
}

void borrar_pesos(double* pesos){
	/* codigo */
	if(pesos){
		/* sentencias */
		free(pesos);
		pesos = NULL;
	}
}

void borrar_nodos(Nodo** nodos, int dim_x, int dim_y){
	/* codigo */
	if(nodos){
		/* sentencias */
		int i,j;
		for(i=0;i<dim_y;i++){
			/* sentencias */
			for(j=0;j<dim_x;j++){
				/* sentencias */
				borrar_pesos((*(nodos+i)+j)->pesos);
			}
			free(*(nodos+i));
			*(nodos+i) = NULL;
		}
	}
}

void borrar_mapa(Mapa* mapa, int long_x, int long_y){
	/* codigo */
	if(mapa){
		/* sentencias */
		borrar_nodos(mapa->nodos,long_x,long_y);
		free(mapa);
		mapa = NULL;
	}
}