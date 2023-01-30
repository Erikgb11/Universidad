#include <iostream>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int Perfecto(int x);
void MostrarPerfectos(int x);
void MostrarPerfectos(int x){
	printf("El numero %d es perfecto\n",x);
}
int Perfecto(int x){
	int a=0,k=0;
	for(int i=1;i<=x;i++){
    	if (x%i==0 && x!=i)
    		a=i+a;
	}
	if(a==x)
    	MostrarPerfectos(a);	
  	return 0;		
}
int main(){
	for(int j=1;j<=100000000;j++){
		Perfecto(j);
	}
}
