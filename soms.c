/******************************************************************************
Mapas AutoOrganizados (SOMs) - Aplicacion.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "soms.h"

int main(){
	int dimns = 2;
	int dim_x = 1;
	int dim_y = 1;
	if(dimns && dim_x && dim_y){
		Mapa* mapa;
		iniciar_mapa(&mapa,dimns,dim_x,dim_y);
		mostrar_datos_mapa(mapa);
		destruir_mapa(&mapa,dim_x,dim_y);
		printf("\nLibero la memoria.\n");
	}
	else{
		printf("\n<dimension> <dim_X> <dim_Y>\n");
	}

	return 0;
}
