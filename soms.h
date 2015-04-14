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

