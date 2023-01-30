#include<stdio.h>
#include <stdlib.h>
 
int main(){
	int n, i, j,aux,c, *l; 
    printf("Ingrese un numero (el programa dara los numeros primos hasta ese numero): ");
	scanf("%d",&n);
	l = (int *)calloc( n + 1, sizeof(int) ); 
	for (i = 2; i <= n; i++){
		if (l[i] == 0){ 
			for (j = 2; ;j++){
				aux = i * j;
				if (aux > n) 
					break;
				l[aux] = 1; 
			}
		}
	}
	printf("Los numeros primos son:\n");
	for (i = 2; i <= n; i++){
		if (l[i] == 0){
			printf("%d \n",i);
			c++;
		}
	}

	printf("\n");
	printf("Se imprimieron una cantidad de %d numeros primos", c);
    return 0;
}
