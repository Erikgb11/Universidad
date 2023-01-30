#include <iostream>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int tam;
	printf("Ingresa el numero de elementos de arreglo:\n");
	scanf("%d",&tam);
	int arreglo [tam];
	int arreglo2 [tam];
	int arreglo3 [tam];
	int longitud = sizeof(arreglo);
	longitud = longitud/4; // se divide entre 4 por que 1 int tiene 4 byts 
	printf("\nLa longitud del arreglo es de %d \n ",longitud);
	//hacemos q guarde numeros aleatorios
	srand(time(NULL));
	int i;
	for(int i=0;i<longitud;i++){
	arreglo[i]=rand()%2;	
	arreglo2[i]=rand()%2;
	}
	printf("\nArreglo 1:\n");
	for ( i=0;i<longitud;i++){
	printf("Arreglo 1 en la pocision %d --> %d \n",i+1,arreglo[i] );
	}
	printf("\nArreglo 2:\n");
	for ( i=0;i<longitud;i++){
	printf("Arreglo 2 en la pocision %d --> %d \n",i+1,arreglo2[i] );
	} 
	for(int i=0;i<longitud;i++){
		if(arreglo[i]&arreglo2[i]){//aqui ya compara 
				arreglo3[i]=1;
		}else{
			arreglo3[i]=0;
		}
		int decimal=0;
	}
	printf("\nResultado del AND:\n");
	for ( i=0;i<longitud;i++){
		printf("Resultado en la pocision %d --> %d \n",i+1,arreglo3[i] );
	}
	// binario a decimal
	int dec=0;
	int j=0;
	for ( i=0;i<longitud;i++){
		dec=dec+(arreglo3[i]*pow(2,i));
	}
	printf("el numero en decimal es %d",dec);
	return 0;
}
