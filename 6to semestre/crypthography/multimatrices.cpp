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
	for(int i=0;i<8;i++){//hace un for de 8
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,BIT_GET(a,7));//la posicion i que es 0 se le da el valor 7
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1
}
unsigned char corrimiento2(unsigned char b){
	unsigned char a=b;	
	for(int i=0;i<8;i++){//hace un for de 8
		if(i==0){//si i es igual a 0
			BIT_WRITE(b,i,0);//la posicion i que es 0 se le da el valor de 0
		}else{
			BIT_WRITE(b,i,BIT_GET(a,i-1));//de otro modo se le da el valor i-1, esto despues de un analisis que se llevo a cabo
		}
	}
	return b;//returna n1	
}
int numerosuno(unsigned char a){
	int conta=0;
	for(int i=0;i<8;i++){//se hace un for hasta 8
		if(BIT_GET(a,i)!=0){//se obtiene el valor i de a y si es diferente de 0
			conta++;//aumenta el contador
		}
	}
	return conta;//y lo retorna
}
void posiunos(unsigned char a,int *unos){
	int conta=0;
	for(int i=0;i<8;i++){//se hace un for hasta 8
		if(BIT_GET(a,i)!=0){//se obtiene el valor i de a y si es diferente de 0
			unos[conta]=i;//se agrega el valor de i a un array para guardar la posicion
			conta++;//se aumenta el contador
		}
	}
	return;
}
unsigned char modu(unsigned char a, unsigned char b){
	int z=ultimouno(a);//se obtiene la posicion del ultimo uno en a
	unsigned char modu=27;//el valor del residuo 
	unsigned char resultados[z];
	resultados[0]=b;//se da el valor de b a la primera posicion del array de los resultados
	for(int i=1;i<=z;i++){//un if hasta z, o la ultima posicion del 1 en a
		if(BIT_GET(b,7)==0){//si el valor del primer bit es 0
			b=corrimiento(b);//hace un corrimiento a la izquierda
		}else if(BIT_GET(b,7)!=0){//si es diferente
			b=corrimiento2(b);//se hace un corrimiento con corrimiento 2
			b=b^modu;//hace un xor con el residuo
		}
		resultados[i]=b;//se agregan los valores de b un array
	}
	int lenght=numerosuno(a);//se saca el valor de los numeros 1 en a
	int unos[lenght];//se hace un array con esa longitud
	posiunos(a,unos);//y se guardan las posiciones de dichos 1's
	unsigned char resultado=resultados[unos[0]];
	for(int i=1;i<lenght;i++){
		resultado=resultado^resultados[unos[i]];//luego se sacan las posiciones y se hacen los xor dependiendo de las posiciones
	}
	return resultado;//se retorna el resultado
}
int main(){
	unsigned char primer[4][4]={{2,3,1,1},{1,2,3,1},{1,1,2,3},{3,1,1,2}};// se inicializa la primera matriz
	unsigned char segundo[4][4]={{135,242,77,151},{110,76,144,236},{70,231,74,195},{166,140,216,149}};//la segunda
	unsigned char res[4][4];//la de resultado
	for (int a = 0; a <4; a++) {//se hace un for
    	for (int i = 0; i <4; i++) {//dentro otro for
	        unsigned char suma = 0;//se inicializa la variable suma que guardara los xor
	        int cont=0;//un contador
	        for (int j = 0; j <4; j++) {//se hace un ultimo for
	            if(cont>0){//si el contador es mayor a 0 entonces hace un xor de suma y la multiplicacion
	            	suma=suma^(modu(primer[i][j],segundo[j][a]));
				}else{//si no solo guarda el valor de la multiplicacion 
					suma=(modu(primer[i][j],segundo[j][a]));
				}
				cont++;//se incrementa el contador
	        }
	        res[i][a] = suma;//se guarda el valor en res
		}
	}
	//despues se imprimen las matrices
	printf("La primer matriz es: \n");//la primera
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%X ",primer[i][j]);
		}
		printf("\n");
	}
	printf("La segunda matriz es: \n");//la segunda
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%X ",segundo[i][j]);
		}
		printf("\n");
	}
	printf("Y finalmente el resultado de la multiplicacion es:\n");//el resultado
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			printf("%X ",res[i][j]);
		}
		printf("\n");
	}
}
