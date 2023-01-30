//elaborado por Gonzalez Bocio Erik Alexander
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef MAX
#define MAX 100
#endif
#define BIT(x)         (1<<(x))
#define BIT_GET(x,b)   ((x) & BIT(b))
#define BIT_SET(x,b)   ((x) |= BIT(b))
#define BIT_CLEAR(x,b) ((x) &= ~BIT(b))
#define BIT_TOGGLE(x,b)  ((x) ^= BIT(b))
#define BIT_WRITE(x,b,v) ((v)? BIT_SET(x,b) : BIT_CLEAR(x,b))
#define ES_PAR(x) (!BIT_GET(x,0))
#define SWAP1(x,y) (x = x ^ y ,  y = x ^ y ,  x = x ^ y )
#define SWAP2(x,y) (x^=y^=x^=y)
#define SWAP3(x,y) (x^=y^=x^=y^=x^=y^=x^=y^=x^=y)
unsigned binario(long int binario){//esta funcion pasa de un long int a un unsigned 
	int exp=0;
	unsigned decimal=0;
   	while((binario/10)!=0)///mientras el long int sea diferente de 0
   	{
           int digito = binario % 10;// digito=binario modulo 10
           decimal = decimal + digito * pow(2.0,exp);//decimal= decimal +digito+ exp al cuadrado
           exp++;//se incrementa exp
           binario=(binario/10);//se hace un llamado recursivo metiendole binario/10
   	}
   	decimal=decimal + binario * pow(2.0,exp);//decimal=decimal+binario+exp al cuadrado
	return decimal;//returna decimal
}

void binary(unsigned char n,int t)
{
    unsigned i;
    for (i = 1 <<t-1; i > 0; i /= 2)//Se hace la impresión de t-1 cantidad de bits
        if(n & i){//Si se cumple el if
            printf("1");//Imprime 1
        }
        else//Si no
            printf("0"); //1
}
int ultimouno(unsigned char a){
	unsigned i;
	int t=8;
	int c=7,c2=0;
    for (i = 1 <<t-1; i > 0; i /= 2){//Se hace la impresión de t-1 cantidad de bits
        if(a & i){//Si se cumple el if
        	c=c-c2;
			return c+1;	
        }else{
        	c2++;
		}
	}
	return c;	
}
unsigned char corrimiento(unsigned char b){
	unsigned char a=b;	
	for(int i=0;i<8;i++){//hace un for de 4
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,BIT_GET(a,7));//la posicion i que es 0 se le da el valor 3
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1
}
unsigned char corrimiento2(unsigned char b){
	unsigned char a=b;	
	for(int i=0;i<8;i++){//hace un for de 4
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,0);//la posicion i que es 0 se le da el valor 3
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1	
}
int numerosuno(unsigned char a){
	int conta=0;
	for(int i=0;i<8;i++){
		if(BIT_GET(a,i)!=0){
			conta++;
		}
	}
	return conta;
}
void posiunos(unsigned char a,int *unos){
	int conta=0;
	for(int i=0;i<8;i++){
		if(BIT_GET(a,i)!=0){
			unos[conta]=i;
			conta++;
		}
	}
	return;
}
unsigned char modu(unsigned char a, unsigned char b){
	int z=ultimouno(a);
	unsigned char modu=27;
	unsigned char resultados[z];
	resultados[0]=b;
	for(int i=1;i<=z;i++){
		if(BIT_GET(b,7)==0){
			b=corrimiento(b);
		}else if(BIT_GET(b,7)!=0){
			b=corrimiento2(b);
			b=b^modu;
		}
		resultados[i]=b;
	}
	int lenght=numerosuno(a);
	int unos[lenght];
	posiunos(a,unos);
	unsigned char resultado=resultados[unos[0]];
	for(int i=1;i<lenght;i++){
		resultado=resultado^resultados[unos[i]];
	}
	return resultado;
}
int main(){
	int n, opcion;
	unsigned char res;
	long int cadena;
	printf("\n");
	printf("Ingrese el valor de la cadena a\n");//pedimos la cadena a trabajar
	scanf("%ld",&cadena);
	unsigned char a;
	a=binario(cadena);
	printf("Ingrese el valor de la cadena b\n");//pedimos la cadena a trabajar
	scanf("%ld",&cadena);
	unsigned char b;
	b=binario(cadena);
	res=modu(a,b);
	binary(res,8);
	printf("\n");
}
